// Room: /d/city/guangchangdong.c

inherit ROOM;

void create()
{
	set("short", "�㳡��");
	set("long", @LONG
���ǹ㳡�Ķ��ࡣ������һ�ҳ����У���Ȼ��Ϊ��վ�ṩ����ġ�ż����
��ߴ���һ�����˻���������������Ǯׯ���͵�ı�����ˣ�������Ĵ�·
��ȥ��ֱ�ﾩ�ǡ�
LONG
	);
        set("outdoors", "����");

	set("exits", ([
	        "east" : __DIR__"chemahang",
	        "west" : __DIR__"guangchang",
		"north" : __DIR__"beidajie3",
		"south" : __DIR__"dongdajie3",
	]));

	set("coor/x",120);
  set("coor/y",-10);
   set("coor/z",0);
   set("coor/x",120);
  set("coor/y",-10);
   set("coor/z",0);
   set("coor/x",120);
  set("coor/y",-10);
   set("coor/z",0);
   setup();
}

