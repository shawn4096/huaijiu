// Room: /d/village/shilu4.c

inherit ROOM;

void create()
{
        set("short", "��ʯ·");
        set("long", @LONG
����һ��������С���ӣ�ϡϡ����ķֲ��ż�ʮ�������෿��������
���˼Ҳ��࣬���Ҵ�����ܼ���������һ�����������ʯ·�������Ǽ�
�ӻ��̣���Ҫ����һЩ�ο���ɽ�õĶ�����
LONG
        );
        set("exits", ([
	"east"  : __DIR__"shilu6",
	"west"  : __DIR__"zhongxin",
	"north" : __DIR__"zahuopu",
]));
        set("no_clean_up", 0);
        set("outdoors", "��ɽ");

        set("coor/x",10);
  set("coor/y",100);
   set("coor/z",0);
   setup();
}


