// Room: /d/village/zhongxin.c

inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�����Ǵ��ӵ����ģ�һ��ƽ̹�Ĺ㳡��ÿ�����մ�Ⱦ����⡣�㳡��
���пô�����ƽ�ղ��෹�ᣬ�������Ů���ٶ�����������̸��˵�ء�
�����м�����ȶѡ�
LONG
        );
        set("exits", ([
		"northwest" : __DIR__"caidi",
		"northeast" : __DIR__"caidi",
		"south" : __DIR__"shilu2",
		"east"  : __DIR__"shilu4",
		"west"  : __DIR__"shilu3",
	]));

        set("objects", ([
                __DIR__"npc/boy": 1,
                __DIR__"npc/girl": 1,
        ]) );

        set("no_clean_up", 0);
        set("outdoors", "��ɽ");

        set("coor/x",0);
  set("coor/y",100);
   set("coor/z",0);
   setup();

}
