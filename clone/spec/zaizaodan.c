
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name (HIR BMAG"�������쵤"NOR, ({ "zaizao dan"}));
	set("long","����һ���Ժ����ڡ������ǧ��ѩ�������Σ��Լ�����ʯ��ȿ�����ҩ���ƶ�\n�ɵĻ������쵤�������Ժ����������������Է����仯��\n");

	set("unit","��");
	set_weight(100);
	set("value",30);
        set("no_cun", 1);
        set("no_drop", 1);
        set("no_give", 1);
	set("no_get", "�������������뿪�Ƕ���\n");
	set("treasure",1);	
	set("degree",1);
	set("desc","�����޸��������ԣ�������Ҫ�۳�exp");
	set("credit",500);
	
	setup();
}

void init()
{
	add_action("do_eat","fu");  
}

int do_eat(string arg)
{

	object me=this_player();
	    
	if (!arg || arg!="zaizao dan")
      		return notify_fail("��ʹ�� fu zaizao dan�������������ԡ�\n");
        me->set_temp("cgift",1);
        write(HIY"����һ�ε����������ԵĻ��ᣬ��������֮ǰʹ��cgiftָ����е�����\n"NOR);
        destruct(this_object());
        return 1;   

}