// Room: /u/firefox/miao.c

inherit ROOM;

void create()
{
        set("short", "Ӣ�ҷ�����");
        set("long", @LONG
�������Ӣ�Ҹ�����������Ǻ����ҷ��ˣ����������Ҹ�������������
Ů��Ӧ�˼�Ůÿ��ص�Ӣ�ҷ�����������Ը������λ�γ��İ����������飬
�չ˺����ͬ�н��á�
LONG    );
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"winmo",
        ]));
        set("objects", ([
                __DIR__"npc/xiangnu" : 2,
	]));
        set("no_fight", 1);
        set("coor/x",40);
  set("coor/y",10);
   set("coor/z",0);
   set("coor/x",40);
  set("coor/y",10);
   set("coor/z",0);
   set("coor/x",40);
  set("coor/y",10);
   set("coor/z",0);
   setup();
}
