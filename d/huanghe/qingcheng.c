// by xiaoyao

#include <room.h>
#include <wanted.h>

inherit ROOM;
void create()
{
	set("short", "���");
	set("long", @LONG
���λ�ھ�Զ�������ٶ�ʮ����ϰ�ʮ��������ݣ���Ϊ��ǣ�
��ʵֻ�Ǹ�С����Ϊ�ش���ȥ���ĵ�Ҫ�壬����������ĺʹ��ε���
�ö����뾭����������������������֡�
LONG );
	set("exits", ([
		"north" : __DIR__"shamo",
		"east"  : __DIR__"hetao",
	]));

	set("outdoors", "�ƺ�");
	set("coor/x",100);
  set("coor/y",120);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",120);
   set("coor/z",0);
   setup();
}

int valid_leave(object me, string dir)
{
	if (dir == "north" && is_wanted(me))
		return 0;
	return ::valid_leave(me, dir);
}
