// Room: /d/dzd/xiliu1.c
#include <ansi.h>
#define XJNO 1
#include "dmd.h"

void create()
{
	set("short","Ϫ��");
	set("long",@LONG
�ߵ������ͻȻ��ǰһ�����峺��Ϫˮ˳�����¡�Ϫ�߳��������滨��ݣ�ɢ����Ũ��
����������ϸ�����ţ���������ˮ�ɻ�ģ���ģ����Ǽ��亱����������ܽ��������һƬ��
��,������һƬ���֡�
LONG
	);
	set("outdoors","���㵺");
	set("exits",([
		"east" : __DIR__"shulin1",
		"west" : __DIR__"caodi1",
		"north" : __DIR__"xiliu2",
		"south" : __DIR__"haitan1",
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
