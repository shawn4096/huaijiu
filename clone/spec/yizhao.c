//ilovemin 2013.12.11
#include <ansi.h>

string long();

inherit ITEM;

void create()
{
	set_name (HIR"�������گ"NOR, ({ "dayan yizhao"}));
	set("long","����һ��������گ��\n");
	set("unit","��");
	set_weight(200);
	set("value",30);
        set("no_cun", 1);
        set("no_give", 1);
        set("no_drop", 1);
	set("no_get", "�������������뿪�Ƕ���\n");
	set("treasure",1);	
	set("degree",1);
        set("desc","����Ľ��֮����˫���Ľ�����Ʒ��");
	set("credit",50);
	setup();
}

void init()
{
	add_action("do_use","read");
  
}

string long()
{
        string msg;

               msg = "���������گ�Ǵ��������ǰ�Ĵ���گ�飬�����ᵽ�˹������������䡣\n"
                      "�����Ӧ����ϸ�ж���read��һ��Ϊ�á�\n";

        return msg;
}

int do_use(string arg)
{
        object me = this_player();
    
        if (me->is_busy())
                return notify_fail("����������æ��\n");

        if (me->is_fighting())
                return notify_fail("�㻹�ǰ���ս���ɡ�\n");

        if (arg && id(arg))
        {
                message_vision(HIW "$N" HIW "��ϸ���ж��Ŵ������گ��\n" NOR, me);
                tell_object(me, HIY "���Ѿ�֪�����������ڣ�����ж��ɡ�\n" NOR);
                me->set_temp("djsj",1);
                destruct(this_object());
                return 1;
                
        }
}	 