// /d/wudang/sanqingdan.c  �����
// by ydh
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIY"�����"NOR);
        set("long", @LONG
���������������������䵱�ɻ�͵ĵص㡣���ŵ�������Ԫʼ����
���鱦������������м��Ǹ�����Ĵ��㰸����ǽ���ż���̫ʦ�Σ����Ϸ�
�ż������š�����������Ĺ㳡���ϱ����䵱���ء�
LONG                           
        );
        set("exits", ([
                "south" : __DIR__"xiaolu1",
                "north" :__DIR__"guangchang",
        ]));

        set("objects",([
                "/kungfu/class/wudang/song" : 1,

        ]));

	set("valid_startroom", 1);

        set("coor/x",-20);
  set("coor/y",-70);
   set("coor/z",100);
   setup();
        "/clone/board/wudang_b"->foo();
}
/*
void init()
{
        object me;
	int lvl;
        mapping learned;

        me = this_player();

	lvl = me->query_skill("taiji-shengong", 1);
	learned = me->query_learned();
	me->delete_skill("taiji-shengong");
	if (lvl > 0) {
		me->delete_skill("yinyun-ziqi");
		me->set_skill("yinyun-ziqi", lvl);
		if (mapp(learned) && learned["taiji-shengong"] > 0)
			me->improve_skill("yinyun-ziqi",
				learned["taiji-shengong"], 1);
		write(HIG "ϵͳ�ѽ����ġ�̫���񹦡�ת��Ϊ������������\n" NOR);
	}
	if (me->query_skill_mapped("force") == "taiji-shengong")
		me->map_skill("force", "yinyun-ziqi");
} */
