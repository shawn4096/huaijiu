// Room: /d/dali/tulin.c
// bbb 1997/06/10 
// Modify By River 98/12
inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
һ̤�����֡���ǧ�˰�̬�����ͣ��ͷ·�ʹ�˽�����һ��������ء��е�
������׶�ƽ���ֱ���죻�е���������ʿ����װ�������е���������Ů������
Զ�����е����������Ӳݴ����������Ұ�����е�ɰʯ���ݣ���¶������
LONG
	);
        set("outdoors", "����");

	set("exits", ([
            "southup" : __DIR__"xiushan",
            "north" : __DIR__"dg1",
	]));

	set("coor/x",-300);
  set("coor/y",-510);
   set("coor/z",-10);
   setup();
}
