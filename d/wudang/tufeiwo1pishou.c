// tufeiwo1.c ����С·
// by pishou 97/6

inherit ROOM;

void create()
{
	set("short", "����С·");
	set("long", @LONG
	������һ��Ƨ��������С·�ϣ���������ɭɭ�����֡�ֻ������ǰ�󣬵���
��������ǵص������֡���ʮ�ɸߵĴ���������һ�飬��ʵ��֦Ҷ��һ�����ɡ
��������գ��������ڵ�˿��Ҳ�ޡ���˵���ﾭ�������˳�û�����ɾ�����
LONG
	);
        set("outdoors", "wudang");

	set("no_sleep_room",1);

	set("exits", ([
		"south" : __DIR__"tufeiwo2",
		"northdown" : __DIR__"wdroad7",
	]));

        set("objects", ([
                __DIR__"npc/tufei2" : 2 ]));

	set("coor/x",40);
  set("coor/y",20);
   set("coor/z",10);
   setup();
}
