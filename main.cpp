// main.cpp
#include <stdio.h>
#include <ctime>
#include <time.h>


#define JANUARY_DAYS 31
#define FEBRUARY_DAYS 28
#define MARCH_DAYS 31
#define APRIL_DAYS 30
#define MAY_DAYS 31
#define JUNE_DAYS 30
#define JULY_DAYS 31
#define AUGUST_DAYS 31
#define SEPTEMBER_DAYS 30
#define OCTOBER_DAYS 31
#define NOVEMBER_DAYS 30
#define DECEMBER_DAYS 31

#define JANUARY 0 
#define FEBRUARY 1
#define MARCH 2
#define APRIL 3
#define MAY 4
#define JUNE 5
#define JULY 6
#define AUGUST 7
#define SEPTEMBER 8
#define OCTOBER 9
#define NOVEMBER 10
#define DECEMBER 11


int mon_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


class CData
{
private:
  tm data;
  
public:
  CData(tm data) {
    this->data = data;
  }

  CData(tm *data) {
    this->data = *data;
  }

  CData(time_t data) {
    tm * pTm = localtime(&data);
    this->data = *pTm; 
  }

  CData(time_t *data) {
    tm * pTm = localtime(data);
    this->data = *pTm; 
  }

  virtual void addDays(long days) {
    while(days > 0)
      {
	if (data.tm_year % 4 == 0)
	  { //весакосный год
	    mon_days[FEBRUARY] = 29;
	  }
	else
	  {
	    mon_days[FEBRUARY] = 28;
	  }
	
	if (data.tm_mday + days > mon_days[data.tm_mon])
	  {
	    days -= (mon_days[data.tm_mon] - data.tm_mday) + 1; // - сколько дней осталось в этом месяце

	    if (data.tm_mon < 11)
	      {
		data.tm_mon ++; // переходим в следующий месяц
	      }
	    else
	      {
		data.tm_year ++;
		data.tm_mon = 0;
	      }
	    
	    data.tm_mday = 1;
	  }
	else
	  {
	    data.tm_mday += days;
	    days = 0;
	  }
      }
  }

  virtual void print()
  {
    char mon_names[12][10] = {"jan\0", "feb\0", "mar\0", "apr", "may\0", "jun\0", "jul\0", "aug\0", "sep\0", "oct\0", "nov\0", "dec\0"};
    printf("\n year: %d, mon: %s, day: %d", data.tm_year + 1900, mon_names[data.tm_mon], data.tm_mday);
  }

public:
  virtual int getMDay()
  {
    return data.tm_mday;
  }

  tm getTm()
  {
    return data;
  }
  
};

class CProfit
{
protected:
  int amount; //purce - кошелёк

public:
  CProfit() {
    this->amount = 0;
    printf("\nprofit constructor");
  }
  
  CProfit(int amount) {
    this->amount = amount;
    printf("\nprofit constructor (%d)", amount);
  }

  ~CProfit() {};
  
protected:
  virtual void inc(int amount) {
    this->amount += amount;
  }

  virtual void dec(int amount) {
    this->amount -= amount;
  }
  
  virtual int getAmount() {
    return this->amount;
  }
};


class CWage : CProfit, CData// зарплата
{
private:
  int payment;

public:
  CWage(tm data, int payment ) :
    CProfit(0),
    CData(data)
  {
    this->payment = payment;
  }
  virtual ~CWage() {};

  virtual void inc()
  {
    this->CProfit::inc(payment);
  }

  virtual int getAmount()
  {
    return this->CProfit::getAmount();
  }

  virtual int getMDay()
  {
    return this->CData::getMDay();
  }

  virtual void operator =(int payment)
  {
    this->payment = payment;
  }
};

class CAdvance : CProfit, CData
{
private:
  int payment;
public:
  CAdvance(tm data, int payment) :
    CProfit(0),
    CData(data)
  {
    this->payment = payment;
  };

  virtual ~CAdvance() {};
  
  virtual void inc()
  {
    this->CProfit::inc(payment);
  }


  /*virtual int getAmount()
  {
    return this->CProfit::getAmount();
    }*/
};

class CHumAid : CProfit// гуманитарная помощь
{
  
};


class CPerMonthProfit : CWage
{
public:
  CPerMonthProfit(tm data, int payment) :
    CWage(data, payment) {};

  virtual void inc() {
    CWage::inc();
  }

  virtual int getAmount() {
    return CWage::getAmount();
      }

  bool checkDay(tm data) {
    if (data.tm_mday == CWage::getMDay())
      {
	printf("\ntime fot payment! :)");
	inc();
	return true;
      }
    return false;
  }

  virtual void operator =(int payment)
  {
    this->CWage::operator=(payment);
  }
  
};


class purce
{
private:
  int purce;

public:
  void addPerMonthFlow(CProfit)
  {}

  
};


int main(int argc, char* argv[])
{
  tm wdata = {0};
  wdata.tm_mday = 8;
  
  CPerMonthProfit m_wayge(wdata, 26000);
  
  CData data(time(NULL));

  for(int i = 0; i < 60; i++)
    {
      data.addDays(1);
      if(m_wayge.checkDay(data.getTm()))
	{
	  data.print();
	  printf("\n  purce: %d", m_wayge.getAmount());
	}
    }

  m_wayge = 100000;
  
  for(int i = 0; i < 60; i++)
    {
      data.addDays(1);
      if(m_wayge.checkDay(data.getTm()))
	{
	  data.print();
	  printf("\n  purce: %d", m_wayge.getAmount());
	}
    }
  
  printf("\nGoodBy!\n");
  
}
