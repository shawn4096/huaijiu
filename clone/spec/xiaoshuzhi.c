//flowray 2005.6.20
#include <ansi.h>

string long();

inherit ITEM;

void create()
{
	set_name (HIG"С��֦"NOR, ({ "xiao shuzhi"}));
	set("long","����һ֦С��֦��\n");
	set("unit","֦");
	set_weight(100);
	set("value",30);
        set("no_cun", 1);
        set("no_drop", 1);
        set("no_give", 1);
	set("no_get", "�������������뿪�Ƕ���\n");
	set("treasure",1);	
	set("degree",1);
        set("desc","˫�ֻ����Ľ�����Ʒ��");
	set("credit",50);
	setup();
}

void init()
{
	add_action("do_use","use");
  
}

string long()
{
        string msg;

               msg = "����һ֦" + name() + NOR + "���������ĸ������ĺ��Ӹո��۶ϵġ�\n"
                      "�ֳ���֦���㲻������(use)����ɳ��������Ϳѻһ����\n";

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
                message_vision(HIW "$N" HIW "ͯ��δ����˫�ָ���һ��С��֦����ɳ���л�����������ͷ��\n" NOR, me);
                tell_object(me, HIY "��о�˫�������ˡ�\n" NOR);
                me->set_temp("hubo",1);
                destruct(this_object());
                return 1;
                
        }
}	 