// /d/jiaxing/houyuan ��Ժ
// by shang 97/6

inherit ROOM;

void create()
{
        set("short", "��Ժ");
	set("long", @LONG
������½��ׯ��Ժ������ǽͷ������һ���к���������ȥժ��������
ǽ�߻������ż����к�Ů����
LONG
	);

	set("exits", ([
                "north" : __DIR__"dating",
	]));

        set("outdoors", "����");
	set("coor/x",150);
  set("coor/y",-350);
   set("coor/z",20);
   setup();
}

