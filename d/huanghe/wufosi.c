// by XiaoYao

#include <room.h>

inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
������һ����������������Χȫ��ɳ������������Ѿ���������
���п������ɳ����ң��Ӱ���Ľ���������ϡ���Ա���������¡���
���֣�Ψһ���������Ľ����Ǵ����ݶ���ȫ�ǿ�����ǿ���������紵
�����������ġ���---��---������
LONG );
	set("exits", ([
		"south"     : __DIR__"shimen",
	]));

	set("coor/x",100);
  set("coor/y",160);
   set("coor/z",0);
   setup();
}

