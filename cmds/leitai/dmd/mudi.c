// Room: /d/dzd/mudi.c

#include <ansi.h>
#include "dmd.h"
#define XJNO 3

void create()
{
	set("short","�ּ�Ĺ��");
	set("long",@LONG
�����Ǻ�ɭ�ֵ����ĵش���ȴһ����Ҳû��,������������һ����Ĺ��Ĺ��(mubei)�����ͺͺ�ģ�
�����Լ��Щ�ּ������㲻������ϸ��(kan)һ�¡�
LONG
	);
	set("outdoors","���㵺");
	set("exits",([
		"east" : __DIR__"senlin5",
		"west" : __DIR__"senlin4",
		"north" : __DIR__"senlin7",
		"northeast" : __DIR__"senlin8",
		"northwest" : __DIR__"senlin6",
		"southeast" : __DIR__"senlin3",
		"southwest" : __DIR__"senlin2",	
	]));
	set("item_desc",([
		"mubei" : "����һ��Ĺ���������ͺͺ�ģ������Լ��Щ�ּ���\n",
		"fenmu" : "һ����֪���ķ�Ĺ�����泤����Ұ�ݡ�\n",
	]));
	setup();
}

void init()
{
        object me;
        me = this_player();
        add_action("do_jie", "jie");

        if (interactive(me) 
         && ! me->is_fighting()
         && me->query_temp("dmd/done") < 9
         && !random(3)
         && me->query_temp("marks/�´�������3") == XJNO){
                remove_call_out("greeting");
                call_out("greeting", 0, me);
        }
}

int do_kan(string arg)
{
	object me = this_player();
	if(me->is_busy() || me->is_fighting())
		return notify_fail("����æ���ء�\n");
	if(!arg || arg=="" || arg!="mubei")
		return notify_fail("��Ҫ��ʲô?\n");
	message_vision(HIY"Ĺ����д��������:\n\n"NOR HIW"ʮ��������ãã����˼������������ǧ��·أ��޴���������
��ʹ���Ӧ��ʶ�������棬����˪��\n\nҹ�����κ����磬С����������ױ��������ԣ�Ω����ǧ�У�
�������곦�ϴ�������ҹ�����ɸڡ�\n\n"NOR,me);
	message_vision(HIB"�������״ʣ��㲻�ɵ��������Լ����������£���������,���Ը��ӡ�\n"NOR,me);
	return 1;
}
