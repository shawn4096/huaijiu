//flowray 2005.6.20
#include <ansi.h>

string long();

inherit ITEM;

void create()
{
	set_name (HIR"������"NOR, ({ "jieyi ling"}));
	set("long","һöЧ�µ���������������ŷ���԰�������������ơ�\n");
	set("unit","ö");
	set_weight(100);
	set("value",30);
        set("no_cun", 1);
        set("no_give", 1);
        set("no_drop", 1);
	set("no_get", "�������������뿪�Ƕ���\n");
	set("treasure",1);	
	set("degree",1);
        set("desc","���ܲ�ͨ����Ľ�����Ʒ��");
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

               msg = "����һö" + name() + NOR + "��������"
                      "�Ѿ�������ʱ�ˡ�\n�������˽��壬���������ʹ��(use)���ơ�\n";

        return msg;
}

int do_use(string arg)
{
        object me = this_player();

        int na = this_object()->name();
      
        if (me->is_busy())
                return notify_fail("����������æ��\n");

        if (me->is_fighting())
                return notify_fail("�㻹�ǰ���ս���ɡ�\n");

        if (arg && id(arg))
        {
                message_vision(HIW "$N" HIW "�ֳ֡�" NOR + na + HIW
                               "�����������˵��Ի�����������ʵ�����ģ��������������˹�¾��\n" NOR, me);
                tell_object(me, HIY "����ú�����ӿ��ֻ��Ѱ��־ͬ����֮�ˣ��ݺὭ���������\n" NOR);
                me->set_temp("jieyi",1);
                destruct(this_object());
                return 1;
                
        }
}	 