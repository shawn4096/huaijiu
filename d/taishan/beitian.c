// Room: /d/taishan/.c
// Date: CSWORD 96/03/25

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
����λ��ʯ��ɽ�ı�´����᷶��ı�����ڣ�·����һʯ����
����д�š����䡹���֡�
LONG
	);

	set("exits", ([
		"southdown" : __DIR__"zhangren",
	]));

	set("outdoors", "taishan");
	set("coor/x",160);
  set("coor/y",230);
   set("coor/z",120);
   setup();
}

