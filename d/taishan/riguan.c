// Room: /d/taishan/.c
// Date: pishou 97/6

inherit ROOM;

void create()
{
	set("short", "�¹۷�");
	set("long", @LONG
������λ�������������ɽ�룬��ʯ�ܴأ���ߵĵط�һʯ
׿������Ϊ���ӷ塣�����߱���̩ɽ�������š�
LONG
	);

	set("exits", ([
		"westup" : __DIR__"yuhuang",
		"eastup" : __DIR__"tanhai",
	]));

        set("objects",([
                __DIR__"npc/wei-shi2" : 3,
        ]));


	set("outdoors", "taishan");
	set("coor/x",180);
  set("coor/y",220);
   set("coor/z",100);
   setup();
}

