// by xiaoyao

#include <room.h>

inherit ROOM;

void create()
{
	set("short", "ʯϿ��");
	set("long", @LONG
ʯϿ������ǰ�Ļƺӹʵ������ڱ���Ǵ��СС�Ķ���ʯ������
�����ɸߵĸ��£�ǧ�����֣�������˵�����µĲ�ɣ��Ҫ�������õĻ�
�����������𵽷ǳ�Ư�����ǳ������껨ʯ��
LONG );
	set("exits", ([
		"southwest" : __DIR__"tumenzi",
		"northeast" : __DIR__"bingcao",
	]));
	set("outdoors", "�ƺ�");
	set("coor/x",70);
  set("coor/y",140);
   set("coor/z",0);
   setup();
}

