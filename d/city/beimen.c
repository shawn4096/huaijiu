// /d/city/beimen.c

#include <room.h>

inherit ROOM;

string look_gaoshi();

void create()
{
	set("short", "����");
	set("long", @LONG
���Ǿ������ݳǵı������ˣ����ſ�һ�Ӷӹٱ������̲�����İ��գ�һ
���ֳֳ����������佫�����ſ�Ѳ�ӣ���Щʱ����Ϊ����һ���ķ�˽������
���ң����Գ�͢�԰��²��������������˳�Ҫ���Ĺ�ְ���Ͼ���ն�ˣ�����һ
λ�µ�Ѳ�����ˣ�Ū���������Ļ̻̣�˭�������ڳ��ž��������ŵ�ǽ������
��һֽ��ʾ(gaoshi)��
LONG
	);

	set("item_desc", ([
		"gaoshi" : (:look_gaoshi:),
	]));

	set("exits", ([
		"south" : __DIR__"beidajie1",
		"north" : __DIR__"hsroad1",
	]));
        set("objects", ([
                __DIR__"npc/wujiang" : 1,
                __DIR__"npc/bing" : 2,
        ]));
        set("outdoors", "����");
	set("coor/x",120);
  set("coor/y",30);
   set("coor/z",0);
   set("coor/x",120);
  set("coor/y",30);
   set("coor/z",0);
   setup();
}

string look_gaoshi()
{
 	return FINGER_D->get_killer() + "\n����Ѳ��\n�Գ�֮\n";
}

