//flowray 2005.6.20
#include <ansi.h>


inherit ITEM; 

void create()
{
	set_name (HIW"����滨"NOR, ({ "you tan","flower"}));
	set("long","����һ��������ǧ��������"HIW"����滨"NOR"����˵�����������ഺ��פ?
����Է��ã�"HIY"fu"NOR"�����������ò�\n");

	set("unit","��");
	set_weight(100);
	set("value",3000000);
        set("no_cun", 1);
        set("no_give", 1);
        set("no_drop", 1);
	set("no_get", "�������������뿪�Ƕ���\n");
	set("treasure",1);	
	set("degree",1);
	set("desc","����һ����ò��");
	set("credit",10);
	setup();
}

void init()
{
	add_action("do_eat","fu");
  
}

int do_eat(string arg)
{
	object me=this_player();
	    
	if (!arg)
      		return notify_fail("��Ҫ����ʲô?\n");
      		
	if (arg!="flower" && arg!="you tan")
      		return notify_fail("��Ҫ����ʲô?\n");
      	
      	if (me->query("per")>29)
      		return notify_fail("���Ѿ���Ư����!\n");
      		
	me->add("per",1);
	write(HIW"�����һ������滨����һ�������ظо����������ȫ��\n"NOR);
	destruct(this_object());
	return 1;
}	 