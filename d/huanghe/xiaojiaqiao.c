// by XiaoYao

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "������");
	set("long", @LONG
�����ݺ͹����м䣬������ˮ������������ˮ�ļ����Ӵ������
���ĳߣ�խ�������࣬�ȴ��ѹ����ഫ����䣬����һλ���մ������
������֮�����鼯�ɽ����Ѿ���˽���������ţ��������ݣ����ȶȱ��š�
LONG );
	set("exits", ([
		"east"    : __DIR__"gulang",
	]));
	set("no_clean_up", 0);
	set("outdoors", "�ƺ�");
	set("coor/x",50);
  set("coor/y",90);
   set("coor/z",0);
   setup();
}

