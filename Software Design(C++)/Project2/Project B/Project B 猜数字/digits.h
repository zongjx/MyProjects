#ifndef DIGITS_H
#define DIGITS_H
//**************************************************************************** class digits
class digits
{
	public:
		digits();                                                          //constructor of four digits
		digits(int digits);                                                //constructor of four digits
		~digits();                                                         //distructor of four digits
		void display();                                                    //display the digits
		void setDigits(int);                                               //set digits 
		bool checkFormat(string);                                          //check the format of the digits
		bool checkFormat(int);                                             //check the format of the digits
		int getDig0();                                                     //return the first number of the digits
		int getDig1();                                                     //return the first number of the digits
		int getDig2();                                                     //return the first number of the digits
		int getDig3();                                                     //return the first number of the digits
		void compare(digits);                                              //computer function
		int getValueOnly();                                                //return the number of right value but wrong position
		int getValueAndPosition();                                         //return the number of right value and right position
		void set_getValueOnly();                                           //set the number of right but wrong position value to 0
		void set_getValueAndPosition();                                    //set the number of right value and right position to 0
		digits& operator=(digits&);                                        //reload function
	private:
		int dig[4];                                                        //storge every bits of the digits
		int valueOnly;                                                     //storge the number of A
		int valueAndPosition;                                              //storge the number of B
};
//**************************************************************************** class digits

digits::digits()
{
	int seed;
	seed=time(NULL);
	srand(seed);
	dig[0]=rand()%10;
	dig[1]=rand()%10;
	while(dig[1]==dig[0])
	dig[1]=rand()%10;
	dig[2]=rand()%10;
	while(dig[2]==dig[0]||dig[2]==dig[1])
	dig[2]=rand()%10;
	dig[3]=rand()%10;
	while(dig[3]==dig[0]||dig[3]==dig[1]||dig[3]==dig[2])
	dig[3]=rand()%10;
	valueOnly=0;
    valueAndPosition=0;
}

digits::digits(int digits)
{
	dig[3]=digits%10;
	dig[2]=(digits/10)%10;
	dig[1]=(digits/100)%10;
	dig[0]=(digits/1000)%10;
	valueOnly=0;
    valueAndPosition=0;
}

digits::~digits()
{
	
}

void digits::display()
{
	cout<<dig[0]<<dig[1]<<dig[2]<<dig[3]<<" ";
}

bool digits::checkFormat(string in)
{
	if(in.length()!=4)
	return false;
	else
	{
		int d0,d1,d2,d3;
		d3=in[3]+'0'-96;
		d2=in[2]+'0'-96;
		d1=in[1]+'0'-96;
		d0=in[0]+'0'-96;
		if(d0==d1||d0==d2||d0==d3||d1==d2||d1==d3||d2==d3)
		return false;
		else
		return true;
	}
}

bool digits::checkFormat(int d)
{
	if(9999-d<=0)
	return false;
	else
	{
		int d0,d1,d2,d3;
		d3=d%10;
		d2=(d/10)%10;
		d1=(d/100)%10;
		d0=(d/1000)%10;
		if(d0==d1||d0==d2||d0==d3||d1==d2||d1==d3||d2==d3)
		return false;
		else
		return true;
	}
}

void digits::setDigits(int digits)
{
	dig[3]=digits%10;
	dig[2]=(digits/10)%10;
	dig[1]=(digits/100)%10;
	dig[0]=(digits/1000)%10;
}

int digits::getDig0()
{
	return dig[0];
}

int digits::getDig1()
{
	return dig[1];
}
int digits::getDig2()
{
	return dig[2];
}

int digits::getDig3()
{
	return dig[3];
}

void digits::compare(digits otherdigits)
{
	if(dig[0]==otherdigits.getDig0())
	valueAndPosition++;
	else if(dig[0]==otherdigits.getDig1()||dig[0]==otherdigits.getDig2()||dig[0]==otherdigits.getDig3())
	valueOnly++;
	if(dig[1]==otherdigits.getDig1())
	valueAndPosition++;
	else if(dig[1]==otherdigits.getDig0()||dig[1]==otherdigits.getDig2()||dig[1]==otherdigits.getDig3())
	valueOnly++;
	if(dig[2]==otherdigits.getDig2())
	valueAndPosition++;
	else if(dig[2]==otherdigits.getDig0()||dig[2]==otherdigits.getDig1()||dig[2]==otherdigits.getDig3())
	valueOnly++;
	if(dig[3]==otherdigits.getDig3())
	valueAndPosition++;
	else if(dig[3]==otherdigits.getDig0()||dig[3]==otherdigits.getDig1()||dig[3]==otherdigits.getDig2())
	valueOnly++;
}

int digits::getValueOnly()
{
	return valueOnly;
}

int digits::getValueAndPosition()
{
	return valueAndPosition;
}

void digits::set_getValueOnly()
{
	valueOnly=0;
}

void digits::set_getValueAndPosition()
{
	valueAndPosition=0;
}

digits& digits::operator=(digits& d)
{
	dig[0]=d.getDig0();
	dig[1]=d.getDig1();
	dig[2]=d.getDig2();
	dig[3]=d.getDig3();
	valueOnly=d.getValueOnly();
    valueAndPosition=d.getValueAndPosition();
	return *this;
}
#endif
