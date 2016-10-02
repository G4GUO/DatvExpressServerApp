#include "stdafx.h"
#include <queue>
#include <deque>
#include <list>
#include <queue>
#include "express.h"
#include <malloc.h>

using namespace std;

// tx buffer queue
static queue <UCHAR *> m_tx_q;
// spare buffer pool
static queue <UCHAR *> m_po_q;
// Mutexes
static CRITICAL_SECTION mutex_po;
static CRITICAL_SECTION mutex_tx;
//
// Allocate a new buffer
//
UCHAR *alloc_buff(void)
{
    UCHAR *b;
    EnterCriticalSection( &mutex_po );
    if(m_po_q.size() > 0 )
    {
        b = m_po_q.front();
        m_po_q.pop();
    }
    else
    {
        // No available memory so allocate some
        b = (UCHAR *)malloc(TP_SIZE);
    }
	LeaveCriticalSection( &mutex_po );
    return b;
}
//
// Release a buffer
//
void rel_buff(UCHAR *b)
{
    EnterCriticalSection( &mutex_po );
    m_po_q.push(b);
    LeaveCriticalSection( &mutex_po );
}
//
// Post a buffer to the tx queue
//
void post_buff( UCHAR *b)
{
	EnterCriticalSection( &mutex_tx );
    if(m_tx_q.size() < MAX_Q_LEN)
        m_tx_q.push(b);
    else
        rel_buff(b);// Queue overflow
	LeaveCriticalSection( &mutex_tx );
}
//
// Get a buffer from the tx queue
//
UCHAR *get_buff(void)
{
    UCHAR *b;
	EnterCriticalSection( &mutex_tx );
    if(m_tx_q.size() > 0 )
    {
        b = m_tx_q.front();
        m_tx_q.pop();
    }
    else
    {
        b = NULL;
    }
	LeaveCriticalSection( &mutex_tx );
    return b;
}
int get_buf_qsize(void)
{
	int len;
	EnterCriticalSection( &mutex_tx );
	len = m_tx_q.size();
	LeaveCriticalSection( &mutex_tx );
	return len;
}
//
// Initialise the buffers
//
void buf_init(void)
{
    // Create the mutex
	InitializeCriticalSection(&mutex_po);
	InitializeCriticalSection(&mutex_tx);
}
