//ROOM: /d/dzd/shulin1.c
#include <ansi.h>
#define XJNO 1
#include "dmd.h"

void create()
{
	set("short","����");
	set("long",@LONG
��ľϡ��س��ţ������������Ƭ���֡������ǰ�����ɳ�ĵ��棬������Ϫ���԰���
�ݵ����Ǻ��߶��ˡ�һЩɽʯ�Ӵ��������У������ƺ������һЩ��������ֵ��Ǿ�Ȼ��
����һ˿������
LONG
	);
	set("outdoors","���㵺");
	set("exits",([
		"east" : __DIR__"shulin2",
		"west" : __DIR__"xiliu1",
		"north" : __DIR__"senlin1",
		"south" : __DIR__"haitan2",
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
