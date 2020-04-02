#include "net.h"
//-----------------------------------------------
uint8_t ipaddr_dest[4];
uint16_t port_dest;

char str[30];
char str1[100];
u8_t data[100];
struct tcp_pcb *server_pcb;
__IO uint32_t message_count=0;
//-----------------------------------------------
enum server_states
{
  ES_NONE = 0,
  ES_ACCEPTED,
  ES_RECEIVED,
  ES_CLOSING
};
//-----------------------------------------------
struct server_struct
{
  u8_t state; /* current connection state */
  u8_t retries;
  struct tcp_pcb *pcb; /* pointer on the current tcp_pcb */
  struct pbuf *p; /* pointer on the received/to be transmitted pbuf */
};
struct server_struct *ss;
//-----------------------------------------------
static err_t tcp_server_accept(void *arg, struct tcp_pcb *newpcb, err_t err);
static void tcp_server_connection_close(struct tcp_pcb *tpcb, struct server_struct *es);
static void tcp_server_error(void *arg, err_t err);
static err_t tcp_server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
static void tcp_server_send(struct tcp_pcb *tpcb, struct server_struct *es);
static err_t tcp_server_sent(void *arg, struct tcp_pcb *tpcb, u16_t len);
static err_t tcp_server_poll(void *arg, struct tcp_pcb *tpcb);
void sendstring(char* buf_str);
//-----------------------------------------------
void tcp_server_init(void)
{
	  server_pcb = tcp_new();
	  if (server_pcb != NULL)
	  {
	    err_t err;
	    err = tcp_bind(server_pcb, IP_ADDR_ANY, PORT);
	    if (err == ERR_OK)
	    {
	      server_pcb = tcp_listen(server_pcb);
	      tcp_accept(server_pcb, tcp_server_accept);
	    }
	    else
	    {
	      memp_free(MEMP_TCP_PCB, server_pcb);
	    }
	  }
}
//----------------------------------------------------------
static err_t tcp_server_accept(void *arg, struct tcp_pcb *newpcb, err_t err)
{
  err_t ret_err;
  struct server_struct *es;
  LWIP_UNUSED_ARG(arg);
  LWIP_UNUSED_ARG(err);
  tcp_setprio(newpcb, TCP_PRIO_MIN);
  es = (struct server_struct *)mem_malloc(sizeof(struct server_struct));
  ss = (struct server_struct *)mem_malloc(sizeof(struct server_struct));
  if (es != NULL)
  {
    es->state = ES_ACCEPTED;
    es->pcb = newpcb;
    ss->pcb = newpcb;
    es->retries = 0;
    es->p = NULL;
    tcp_arg(newpcb, es);
    tcp_recv(newpcb, tcp_server_recv);
    tcp_err(newpcb, tcp_server_error);
    tcp_sent(newpcb, tcp_server_sent);
    tcp_poll(newpcb, tcp_server_poll, 0);
    ret_err = ERR_OK;
  }
  else
  {
    tcp_server_connection_close(newpcb, es);
    ret_err = ERR_MEM;
  }
  return ret_err;
}
//----------------------------------------------------------
static void tcp_server_connection_close(struct tcp_pcb *tpcb, struct server_struct *es)
{
  // remove all callbacks
  tcp_arg(tpcb, NULL);
  tcp_sent(tpcb, NULL);
  tcp_recv(tpcb, NULL);
  tcp_err(tpcb, NULL);
  tcp_poll(tpcb, NULL, 0);
  if (es != NULL)
  {
    mem_free(es);
  }
  tcp_close(tpcb);
}
//----------------------------------------------------------
static void tcp_server_error(void *arg, err_t err)
{
}
//-----------------------------------------------
static err_t tcp_server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
	struct server_struct *es;
	err_t ret_err;
	LWIP_ASSERT("arg != NULL",arg != NULL);
	es = (struct server_struct *)arg;
	if (p == NULL)
	{
		es->state = ES_CLOSING;
		if(es->p == NULL)
		{
			tcp_recved(tpcb, p->tot_len);
		}
		else
		{
			//acknowledge received packet
			tcp_sent(tpcb, tcp_server_sent);
			//send remaining data
			tcp_server_send(tpcb, es);
		}
		ret_err = ERR_OK;
	}
	else if(err != ERR_OK)
	{
		  if (p != NULL)
		  {
		    es->p = NULL;
		    pbuf_free(p);
		  }
		  ret_err = err;
	}
	else if(es->state == ES_ACCEPTED)
	{
		  tcp_recved(tpcb, p->tot_len);
		  strncpy(str1,p->payload,p->len);
		  str1[p->len] = '\0';
		  // echo--------------
		  sendstring(str1);
		  // ------------------
		  ret_err = ERR_OK;
	}
	else if (es->state == ES_RECEIVED)
	{
		  if(es->p == NULL)
		  {
		    ret_err = ERR_OK;
		  }
		  else
		  {
		    struct pbuf *ptr;
		    ptr = es->p;
		    pbuf_chain(ptr,p);
		  }
		  ret_err = ERR_OK;
	}
	else if(es->state == ES_CLOSING)
	{
		  tcp_recved(tpcb, p->tot_len);
		  es->p = NULL;
		  pbuf_free(p);
		  ret_err = ERR_OK;
	}
	else
	{
		  tcp_recved(tpcb, p->tot_len);
		  es->p = NULL;
		  pbuf_free(p);
		  ret_err = ERR_OK;
	}
	return ret_err;
}
//-----------------------------------------------
static void tcp_server_send(struct tcp_pcb *tpcb, struct server_struct *es)
{
  struct pbuf *ptr;
  err_t wr_err = ERR_OK;
  while ((wr_err == ERR_OK) &&
    (es->p != NULL) &&
    (es->p->len <= tcp_sndbuf(tpcb)))
  {
    ptr = es->p;
    wr_err = tcp_write(tpcb, ptr->payload, ptr->len, 1);
    if (wr_err == ERR_OK)
    {
      u16_t plen;
      u8_t freed;
      plen = ptr->len;
      es->p = ptr->next;
      if(es->p != NULL)
      {
        pbuf_ref(es->p);
      }
      do
      {
        freed = pbuf_free(ptr);
      }
      while(freed == 0);
      tcp_recved(tpcb, plen);
    }
    else if(wr_err == ERR_MEM)
    {
      es->p = ptr;
    }
    else
    {
      //other problem
    }
  }
}
//----------------------------------------------------------
static err_t tcp_server_sent(void *arg, struct tcp_pcb *tpcb, u16_t len)
{
	struct server_struct *es;
	LWIP_UNUSED_ARG(len);
	es = (struct server_struct *)arg;
	es->retries = 0;
	if(es->p != NULL)
	{
		tcp_server_send(tpcb, es);
	}
	else
	{
		if(es->state == ES_CLOSING)
			tcp_server_connection_close(tpcb, es);
	}
	return ERR_OK;
}
//-----------------------------------------------
static err_t tcp_server_poll(void *arg, struct tcp_pcb *tpcb)
{
	err_t ret_err;
	struct server_struct *es;
	es = (struct server_struct *)arg;
	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
	if (es != NULL)
	{
	  if (es->p != NULL)
	  {
	  }
	  else
	  {
	    if(es->state == ES_CLOSING)
	    {
	      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
	      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
	      tcp_server_connection_close(tpcb, es);
	    }
	  }
	  ret_err = ERR_OK;
	}
	else
	{
	  tcp_abort(tpcb);
	  ret_err = ERR_ABRT;
	}
	return ret_err;
}
//-----------------------------------------------
void sendstring(char* buf_str)
{
	tcp_sent(ss->pcb, tcp_server_sent);
	tcp_write(ss->pcb, (void*)buf_str, strlen(buf_str), 1);
	tcp_recved(ss->pcb, strlen(buf_str));
}
