// Room: /d/dzd/caodi1.c
#include <ansi.h>
#define XJNO 1
#include "dmd.h"

void create()
{
	set("short","�ݵ�");
	set("long",@LONG
������һƬˮ�ݽ�����ʪ�ء�������Ţ���С����紵�������쳤��֮���ֳ������ŵ�
���۰׹ǣ��ƺ��������㣬�˴���Ȼ�ƺ��ž����ˣ�ȴ�ǰ���ɱ��������ͱ�����һ��Ϫ
�����Ѷ�����
LONG
	);
	set("outdoors","���㵺");
	set("exits",([
		"north" : __DIR__"caodi2",
		"east" : __DIR__"xiliu1",
		"southeast" : __DIR__"haitan1",
	]));
	set("objects",([
		__DIR__"npc/snake" : random(2),
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
