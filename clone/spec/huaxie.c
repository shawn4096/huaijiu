//ilovemin 2013.12.11
#include <ansi.h>

string long();

inherit ITEM;

void create()
{
	set_name (HIR"����Ļ�Ь"NOR, ({ "xiuhua xie"}));
	set("long","����һ˫�廨Ь��\n");
	set("unit","˫");
	set_weight(200);
	set("value",30);
        set("no_cun", 1);
        set("no_give", 1);
        set("no_drop", 1);
	set("no_get", "�������������뿪�Ƕ���\n");
	set("treasure",1);	
	set("degree",1);
        set("desc","�貨΢���Ľ�����Ʒ��");
	set("credit",50);
	setup();
}

void init()
{
	add_action("do_use","mail");
  
}

string long()
{
        string msg;

               msg = "��˫�廨Ь�����齻��������ǰ����ٹ�Ѱ�Ҿȱ������\n"
                      "�����Ƕ�����·����ʧ�ˣ�����þ���ͨ����վ�ʼ�(mail)��ȥ��\n";

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
                message_vision(HIW "$N" HIW "��������һƥ�������廨Ь�ʵ��˳�ȥ��\n" NOR, me);
                tell_object(me, HIY "��о������������������\n" NOR);
                me->set_temp("duanyu/ok",1);
                destruct(this_object());
                return 1;
                
        }
}	 