// Room: /d/huashan/dashu.c
// Date: Look 99/03/25

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short",  HIW "ɽ��" NOR);
	set("long", @LONG
������һ�����ɸߵ�ɽ�£���̧ͷһ��������ɽ����������һЩ��֪����
��ҩ���ƺ����Բ������Ե����㲻ס�����Ͽ�����Ȼûע�⵽����û���κγ�
·��
LONG
);

	set("no_clean_up", 0);

	set("outdoors", "��ɽ" );
	setup();
}

void init()
{
        add_action("do_tiao", "tiao");
//        add_action("do_cai", "cai");
}

int do_cai(string arg)
{
	object ob;
        object me = this_player();

	if (arg != "lingzhi")
                return notify_fail("��Ҫ��ʲô��\n");
        if (me->is_busy() || me->is_fighting())
                return notify_fail("����æ���ء�\n");

	if(me->query("family/family_name") !="��ɽ��")
                return notify_fail("һ�������Կ������𣬡������ǻ�ɽ���أ��㻹�ǸϿ��뿪�ɣ���\n");

        if ( (int)me->query("jingli")<400)
        	{
             	write("������̫���ˣ���Ϣһ�°ɣ�\n");
		return 1;
		}
        if(random(20)!=3)
        	{
        	me->add("jingli",-random(300));
        	return notify_fail("���������˰��죬ʲôҲû�ҵ���\n"); 
         	}

	if (present("lingzhi", me))
                return notify_fail("�������Ѿ�����֥���ˣ�ĪҪ̰�����ᣡ\n");
        message_vision("$N���ֲ���һ����֥�ݡ�\n", me);
        ob = new(__DIR__"obj/lingzhi");
        ob->move(me);
	return 1;
}

int do_tiao(string arg)
{
        object me = this_player();
	if (arg != "xiaoxi")
                return notify_fail("��Ҫ����������\n");
        if (me->is_busy() || me->is_fighting())
                return notify_fail("����æ���ء�\n");
	if ((int)me->query("max_neili") < 401)
		return notify_fail("�㳢��������СϪ��ȴ�����Լ�������ȥ��\n");
	message_vision("$Nһ��������԰�����ȥ��\n", me);
	tell_object(me, "�㷢���Լ������˸ղ����ĵط���\n");

        me->receive_damage("jing", 30);
	me->move(__DIR__"xiaoxi");
	message_vision("$N��СϪ�Ǳ����˹�����\n", me);

        me->start_busy(random(2));
        return 1;
}

