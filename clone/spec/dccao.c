//Ilovemin 2016.5.3
#include <ansi.h>


inherit ITEM; 

void create()
{
	set_name (HIG"�ϳ���"NOR, ({ "duanchang cao"}));
	set("long","����һ��ʮ�����ĺ����ٿ�ֲ������٣��Դ���ζȴ���м���Ķ��ԡ�\n");

	set("unit","��");
	set_weight(100);
	set("value",3000000);
        set("no_cun", 1);
        set("no_give", 1);
        set("no_drop", 1);
	set("no_get", "�������������뿪�Ƕ���\n");
	set("treasure",1);	
	set("degree",1);
	set("desc","��˵�������黨֮����ҩ�Ĺؼ����ϡ�");
	set("credit",50);
	setup();
}
