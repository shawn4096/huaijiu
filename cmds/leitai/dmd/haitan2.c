// Room: /d/dzd/haitan2.c
#include <ansi.h>
#define XJNO 2
#include "dmd.h"

void create()
{
	set("short","��̲");
	set("long",@LONG
�������ǰ�ɫ��Ӳ��ɳ�������м����ű��ǵ���Ƭ�ͱ���ˮ��ˢ�ü���⻬����ʯ��
�����һЩ�����˳��ϰ��ĺ���,�����ɫ���ŵ�ɳ̲������һĨ���̡����СС�Ľ�ʯ��
��ɳ̲��,������Щ�ǳ��޴��ƺ����Բ���������һ��СϪ��
LONG
	);
	set("outdoors","���㵺");
	set("exits",([
		"east" : __DIR__"haitan3",
		"west" : __DIR__"haitan1",
		"north" : __DIR__"shulin1",
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
