// sl_dan.c

#include <ansi.h>

inherit ITEM;

void init()
{
	add_action("do_eat", "drink");
	add_action("do_eat", "he");
	add_action("do_eat", "yin");
	//add_action("do_eat", "tun");
}

void create()
{
        set_name(HIG "�ۻƾ�" NOR, ({"xionghuangjiu","jiu","skin"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long",
                "����һ���ۻƾƣ��������̵������ʱ�غȵģ���˵���Է���ҧ��\n");
		set("unit", "��");
		set("no_get", 1);
              set("no_drop", 1);
	}
}

int do_eat(string arg)
{
	object me = this_player();
	if (!living(me)) return notify_fail("�뵱����\n");
	if (!id(arg)) return 0;
	message_vision(HIG "$N����һ��"
	+this_object()->query("name")+
	HIG "����ʱ����ȫ���ȣ�һ�ɾ���ֱ��ͷ�����е���ѬѬ�ġ�\n"
	NOR,me);
       me->set("xionghuangjiu",1);     
       destruct(this_object());
	return 1;
}
