#ifndef __IRQ_H__
#define __IRQ_H__
void inst_irq(unsigned char irq_num, void (*f)());

void timer_irq();
#endif
