// Room: /d/village/shilu3.c

inherit ROOM;

void create()
{
        set("short", "��ʯ·");
        set("long", @LONG
����һ��������С���ӣ�ϡϡ����ķֲ��ż�ʮ�������෿��������
���˼Ҳ��࣬���Ҵ�����ܼ���������һ�������������ʯ·��������
��С�ƹݣ�һ�����ӹ��ڷ����¡�
LONG
        );
        set("exits", ([
	"east"  : __DIR__"zhongxin",
	"north" : __DIR__"jiusi",
	"west" : __DIR__"shilu5",
]));
        set("objects", ([
                __DIR__"npc/poorman": 1 ]) );

        set("no_clean_up", 0);
        set("outdoors", "��ɽ");

        set("coor/x",-10);
  set("coor/y",100);
   set("coor/z",0);
   setup();
}


