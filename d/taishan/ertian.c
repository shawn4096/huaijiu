// Room: /d/taishan/.c
// Date: CSWORD 96/03/25

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
�����ֽС������š���һ��ĵ�ɽ���������ﶼ���ۼ�������
�������̩ɽ��һ�밡�����ǰ���վ���ʮ���̣��ܶ��˶�������
ԥ������
LONG
	);

	set("exits", ([
		"northup" : __DIR__"wudafu",
		"southdown" : __DIR__"huima",
	]));

        set("objects",([
                __DIR__"npc/tiansong" : 1,
                __DIR__"npc/tianbai" : 1,
        ]));
	set("outdoors", "̩ɽ");
	set("coor/x",170);
  set("coor/y",170);
   set("coor/z",60);
   set("coor/x",170);
  set("coor/y",170);
   set("coor/z",60);
   setup();
}

