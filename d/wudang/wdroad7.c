// wdroad7.c ����·

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
		"east" : __DIR__"wdroad6",
		"west" : __DIR__"wdroad8",
 	        "southup" : __DIR__"tufeiwo1",
	]));

	set("coor/x",40);
  set("coor/y",30);
   set("coor/z",0);
   setup();
}

