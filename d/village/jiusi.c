// Room: /d/village/jiusi.c

inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
�����Ǵ��������һ��С������ƽʱ����������Ͼ��ʱ����������ǲ
��һ�߽�����һ������ˮ�ƵĴ̱�ζ��ֱ�����˹��������ӵ�������ż�
�����ӣ������һ��æµ�š�
LONG
        );
        set("exits", ([
		"south" : __DIR__"shilu3",
	]));

/*
        set("objects", ([
                __DIR__"npc/": 2 ]) );
*/
        set("no_clean_up", 0);

        set("coor/x",-10);
  set("coor/y",110);
   set("coor/z",0);
   setup();
}


