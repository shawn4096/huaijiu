// Room: /d/village/shilu2.c

inherit ROOM;

void create()
{
        set("short", "��ʯ·");
        set("long", @LONG
����һ��������С���ӣ�ϡϡ����ķֲ��ż�ʮ�������෿��������
���˼Ҳ��࣬���Ҵ�����ܼ���������һ���ϱ������ʯ·�������Ǽ�
�����̣����˷���������Ϊ����
LONG
        );
        set("exits", ([
  "east"  : __DIR__"tiejiangpu",
  "north" : __DIR__"zhongxin",
  "south" : __DIR__"shilu1",
]));
        set("no_clean_up", 0);
        set("outdoors", "��ɽ");

        set("coor/x",0);
  set("coor/y",90);
   set("coor/z",0);
   setup();
}


