// Room: /d/fuzhou/zahuopu.c

inherit ROOM;

void create()
{
	set("short", "�ӻ���");
	set("long", @LONG
������һ��ר��Ů���õĶ�����С���ӡ�
LONG
	);

	set("exits", ([
                "east" : __DIR__"xijie",
	]));

    set("objects", ([
                 __DIR__"npc/chen" : 1,
    ]) );


	set("indoors", "����");
	set("coor/x",80);
  set("coor/y",-470);
   set("coor/z",0);
   setup();
}

