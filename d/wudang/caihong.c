// /d/wudang/caihong.c �ʺ�(ʯ��)
// by ydh and shang

inherit ROOM;

void create()
{
        set("short", "���ʺ�");
        set("long", @LONG
������ɽ���У������ǾŶɽ�������������֮ˮ���ڴ˽��㣬Ȼ
��ͻȻ��к����ע��ɽ���γ�׳�۵��ٲ���һ����Ȼʯ�����������
Զ���ۿ�����һ�����ʺ硣�����Ͼ��Ƕ��͵�ʮ�����ˡ�
LONG
        );

        set("exits", ([
                "southup" : __DIR__"shibapan",
 "northup" : __DIR__"wangbeipo",
        ]));
        set("objects",([
                __DIR__"npc/youke" : 1,

        ]));

        set("no_clean_up", 0);
        set("outdoors", "wudang");

        set("coor/x",0);
  set("coor/y",-30);
   set("coor/z",50);
   setup();
}
