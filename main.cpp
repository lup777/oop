// main.cpp
#include <stdio.h>
#include <ctime>
#include <time.h>
#include <vector>


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

char mon_names[12][10] = {"jan\0", "feb\0", "mar\0", "apr", "may\0", "jun\0", "jul\0", "aug\0", "sep\0", "oct\0", "nov\0", "dec\0"};

enum enum_months {
  jan = 0,
  feb,
  mar,
  apr,
  may,
  jun,
  jul,
  aug,
  sep,
  oct,
  nov,
  dec
};

class CData
{
private:
  tm data;
  
public:
  CData() {
    this->data.tm_year = 0;
    this->data.tm_mon = 0;
    this->data.tm_mday = 0;
  }
  
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

  CData(int year, enum_months mon, int mday) {
    setData(year, static_cast<int>(mon), mday);
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

  bool setData(int year, int mon, int mday) {
    if( year >= 1900)
      this->data.tm_year = year - 1900;
    this->data.tm_mday = mday;
    this->data.tm_mon = mon;
    return true;
  }

  friend bool operator ==(CData ldata, CData rdata) {
    if ((ldata.getTm().tm_year == rdata.getTm().tm_year) &&
	(ldata.getTm().tm_mon == rdata.getTm().tm_mon) &&
	(ldata.getTm().tm_mday == rdata.getTm().tm_mday))
      return true;
    else
      return false;
  }

  CData& operator ++(void) {
    addDays(1);
    return *this;
  } // prefix

  CData operator ++(int) {
    CData temp = *this;
    ++*this;
    return temp;
  } //postfix

  friend bool operator <(CData ldata, CData rdata) {
    tm left_time = ldata.getTm();
    tm right_time = rdata.getTm();
    if ( mktime(&left_time) < mktime(&right_time))
      return true;
    else
      return false;
  }

  friend bool operator <=(CData ldata, CData rdata) {
    tm left_time = ldata.getTm();
    tm right_time = rdata.getTm();
    if ( mktime(&left_time) <= mktime(&right_time))
      return true;
    else
      return false;
  }

  friend bool operator >(CData ldata, CData rdata) {
    tm left_time = ldata.getTm();
    tm right_time = rdata.getTm();
    if ( mktime(&left_time) > mktime(&right_time))
      return true;
    else
      return false;
  }

  friend bool operator >=(CData ldata, CData rdata) {
    tm left_time = ldata.getTm();
    tm right_time = rdata.getTm();
    if ( mktime(&left_time) >= mktime(&right_time))
      return true;
    else
      return false;
  }

  void operator =(time_t time_) {
    tm *tmp_tm = localtime(&time_);
    this->data = *tmp_tm;
  }

  void operator =(tm time_) {
    this->data = time_;
  }


  virtual void print()
  {
    
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
  }
  
  CProfit(int amount) {
    this->amount = amount;
  }

  ~CProfit() {};
  
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
protected:
  int payment;
  const char * comment;


public:
  CWage(tm data, int payment, const char * comment ) :
    CProfit(0),
    CData(data)
  {
    this->payment = payment;
    this->comment = comment;
  }

  virtual ~CWage() {};

  virtual const char * getComment() {
    return comment;
  }
  
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

  virtual tm getTm()
  {
    return this->CData::getTm();
  }

  virtual void operator =(int payment)
  {
    this->payment = payment;
  }

  virtual int getpayment() {
    return payment;
  }
};


class COnceProfit : CWage {  
public:
  COnceProfit(tm data, int payment, const char * comment) :
    CWage(data, payment, comment) {};

  virtual void inc() {
    CWage::inc();
  }

  virtual int getAmount() {
    return CWage::getAmount();
  }

  virtual int getpayment() {
    return CWage::payment;
  }
  
  virtual const char * getComment() {
    return CWage::comment;
  }

  bool checkDay(tm data) {
    if ((data.tm_mday == CWage::getMDay()) &&
	(data.tm_mon == CWage::getTm().tm_mon) &&
	(data.tm_year == CWage::getTm().tm_year))
      {
	return true;
      }
    return false;
  }

  virtual bool operator ==(tm data) {
    if (checkDay(data) == true)
      return true;
    else
      return false;
  }

  COnceProfit& operator ++() {
    inc();
    return *this;
  }

  COnceProfit operator ++(int) {
    COnceProfit tmp = *this;
    ++*this;
    return tmp;
  }

};

class CPerMonthProfit : CWage
{
public:
  CPerMonthProfit(tm data, int payment, const char * comment) :
    CWage(data, payment, comment) {};

  virtual void inc() {
    CWage::inc();
  }

  virtual int getAmount() {
    return CWage::getAmount();
      }

  virtual int getpayment() {
    return CWage::payment;
  }

  bool checkDay(tm data) {
    if (data.tm_mday == CWage::getMDay())
      {
	return true;
      }
    return false;
  }

  virtual const char * getComment() {
    return CWage::comment;
  }
  
  friend int operator +(CPerMonthProfit lp, CPerMonthProfit rp) {
    return lp.getAmount() + rp.getAmount();
  }

  
  virtual void operator =(int payment)
  {
    this->CWage::operator=(payment);
  }

  virtual bool operator ==(tm data) {
    if (checkDay(data) == true)
      return true;
    else
      return false;
  }

  CPerMonthProfit& operator ++() {
    inc();
    return *this;
  }

  CPerMonthProfit operator ++(int) {
    CPerMonthProfit tmp = *this;
    ++*this;
    return tmp;
  }
  
};



class purce
{
private:
  std::vector<CPerMonthProfit*> p;
  CData data;
  CData endData;
  
public:
  purce() {
    p.empty();
    data = time(NULL);
    endData = time(NULL);
  }
  
  ~purce() {
    for (unsigned int i = 0; i < p.size(); i ++)
      delete p[i];
  }
  
  void addPerMonthFlow(int day, int payment, const char * comment) {
    tm wdata = {0};
    wdata.tm_mday = day;
    p.push_back(new CPerMonthProfit(wdata, payment, comment));
  }

  void addOnceFlow(int year, enum_months mon, int day, int payment, const char * comment) {
    tm wdata = CData(year, mon, day).getTm(); // тестовая гуманитарная помощь
    p.push_back((CPerMonthProfit*)(new COnceProfit(wdata, payment, comment)));
  }
  
  void setStartDate(int year, enum_months mon, int day) {
    data = CData(year, mon, day);
  }

  void setEndDate(int year, enum_months mon, int day) {
    endData = CData(year, mon, day);
  }
  
  void calc() {
    CData sData = data;

    for(CData data = sData; data < endData; data++)
      {
	for (unsigned int i = 0; i < p.size(); i ++)
	  {
	    if (*p[i] == data.getTm())
	      {
		(*p[i])++;
		
		int amount = 0;
		for (unsigned int j = 0; j < p.size(); j++)
		  amount += p[j]->getAmount();
		
	      printf("\n%04d %s %02d |  purce: %7d  ( %s: %d )", 
		     data.getTm().tm_year + 1900,
		     mon_names[data.getTm().tm_mon],
		     data.getTm().tm_mday,
		     amount,
		     p[i]->getComment(),
		     p[i]->getpayment()
		     );
	      }
	  }
      }
    
  }
  
};

//#include <gtk/gtk.h>

int main(int argc, char* argv[])
{
  purce p;

  // ++
  p.addPerMonthFlow(8, 26000, "зарплата lup");
  p.addPerMonthFlow(24, 24000, "аванс lup");
  p.addPerMonthFlow(7, 14000, "Запрлата markovka");
  p.addPerMonthFlow(24, 16000, "аванс markovka");

  // --
  //p.addPerMonthFlow(25, -7000, "парковка");
  p.addPerMonthFlow(20, -5000, "Налоги");
  p.addPerMonthFlow(1, -2000, "Проездной");
  p.addPerMonthFlow(1, -2000, "Заправка");
  //p.addPerMonthFlow(15, -2000, "Заправка");

  // разовые
  p.addOnceFlow(2016, sep, 3, -10000, "замена масла");
  p.addOnceFlow(2016, sep, 30, -4000, "коттедж");
  p.addOnceFlow(2016, oct, 7, -(2500 * 3) , "поездка в Тулу");
  p.addOnceFlow(2017, aug, 26, -400000, "свадьба");
  p.addOnceFlow(2017, sep, 2, -200000, "путешествие");
  p.addOnceFlow(2017, oct, 29, -30000, "ноутбук");
  p.addOnceFlow(2017, mar, 15, -200000, "земля");
  
  p.setEndDate(2017, sep, 15);

  
  p.calc();
  
  printf("\nGoodBy!\n");  
}



  /*  GtkWidget *window;
  GtkWidget *button;
  
  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  button = gtk_button_new_with_label("Привет");

  gtk_window_set_title(GTK_WINDOW(window), "кошелёк");
  gtk_container_set_border_width (GTK_CONTAINER(window), 50);
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_container_add(GTK_CONTAINER(window), button);

  gtk_widget_show_all(window);

  //g_signal_connect(GTK_BUTTON(button), "clicked", G_CALLBACK(welcome), NULL);
  
  gtk_main();
  */
