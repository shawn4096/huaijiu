// by xiaoyao

#include <room.h>
#include <wanted.h>

inherit ROOM;

void create()
{
	set("short", "��Զ");
	set("long", @LONG
��Զ�Ǹ�����С�ĳ��򣬻�ɳ�������ʮ��ĵط���һ���ŵ�����
����������ס�ˡ������������һ��ϴ�����ޣ��ۼ��˲��ٴӱ�����
������Щ�����˵�ǵ����Ƴ��������ͻ�ʺ��������ͱ�ʱ���֡���
Ҳ�Ǿ�Զ���������������߲�Զ���ǻƺӣ�������һ��ƬɳĮ��
LONG );
	set("exits", ([
		"north"     : __DIR__"hongshanxia",
		"south"     : __DIR__"shamo",
	]));

	set("outdoors", "�ƺ�");
	set("coor/x",100);
  set("coor/y",130);
   set("coor/z",0);
   setup();
}

int valid_leave(object me, string dir)
{
	if (dir == "south" && is_wanted(me))
		return 0;
	return ::valid_leave(me, dir);
}
