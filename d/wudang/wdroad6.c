// wdroad6.c ����·

inherit ROOM;

void create()
{
	set("short", "����·");
	set("long", @LONG
������һ����������Ļ���·�ϣ���������ɭɭ�����֡������Ƕ�������
˵���������˳�û�����ɾ�����
LONG
	);
        set("outdoors", "�䵱");

	set("exits", ([
		"east" : "/d/xiangyang/hanshui2",
		"west" : __DIR__"wdroad7",
	]));
        set("objects",([
                "/kungfu/class/wudang/quanjiannan" : 1,
                "/kungfu/class/wudang/qlbz" : 2,
        ]));

	set("coor/x",50);
  set("coor/y",30);
   set("coor/z",0);
   setup();
}

