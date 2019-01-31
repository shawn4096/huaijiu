//ROOM: /d/dzd/senlin1.c

#include <ansi.h>
#include "dmd.h"
#define XJNO 1

void create()
{
	set("short","��ɭ��");
	set("long",@LONG
����һƬһ���޼ʡ���������ԭʼɭ�֣����˺ϱ��Ĵ������滨��ݾ�Ŀ���ǡ�
��ľ���Ӵ���һ�飬��ʵ��֦Ҷ��һ�����ɡ��������գ��������ڵ�˿��Ҳ�ޡ���һ
�߽�������������ɭ�ֵģ��ƺ�˭���۾���ע�����㣬��ĸо������㣬�øϿ��뿪��
LONG
	);
	set("outdoors","���㵺");
	set("exits",([
		"east" : __DIR__"senlin2",
		"west" : __DIR__"xiliu2",
		"south" : __DIR__"shulin1",
		"northeast" : __DIR__"senlin4",
		"southeast" : __DIR__"shulin2",		
	]));
	set("objects",([
		__DIR__"npc/tiger" : 1,
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
















	