// Room: /d/village/shilu5.c

inherit ROOM;

void create()
{
        set("short", "��ʯ·");
        set("long", @LONG
����һ��������С���ӣ�ϡϡ����ķֲ��ż�ʮ�������෿��������
���˼Ҳ��࣬���Ҵ�����ܼ����������Ǽ�С��ÿ�귢���ֺ���ʱ��
�����Ŷ����������������챣�ӡ�
LONG
        );
        set("exits", ([
  "east"  : __DIR__"shilu3",
  "south" : __DIR__"miaoyu",
]));
        set("no_clean_up", 0);
        set("outdoors", "��ɽ");

        set("coor/x",-20);
  set("coor/y",100);
   set("coor/z",0);
   setup();
}
