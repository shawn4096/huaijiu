// Room: /d/huashan/npc/baichi.c
// Date: Look 99/03/25

inherit ROOM;

void create()
{
	set("short", "�ٳ�Ͽ");
	set("long", @LONG
�߹�ǧ�ߴ���ǰ���ּ���һҪ���İٳ�Ͽ���ٳ�Ͽ����ǧ�ߴ����վ�����
��ʮ�ֶ��ͣ��ұ�����������������������
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
		"northdown" : __DIR__"qianchi",
		"eastup" : __DIR__"laojun",
	]));

	set("objects", ([ 
		__DIR__"npc/monkey" : 1,
	]));

	set("no_clean_up", 0);
	set("outdoors", "��ɽ" );

	set("coor/x",60);
  set("coor/y",70);
   set("coor/z",30);
   setup();
}