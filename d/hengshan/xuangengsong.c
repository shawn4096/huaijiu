// Room: /d/hengshan/xuangengsong.c
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "������");
        set("long", @LONG
���ڻ�����������յأ�ȴ��һ����ɣ��䱻��紵������
��¶��ǧ��������ӭ��ͦ��������Ǻ�ɽ������ "������" ��
LONG);
        set("exits", ([ /* sizeof() == 4 */
           "east"      : __DIR__"hufengkou",
        ]));
        set("outdoors", "��ɽ");
        set("no_clean_up", 0);
        set("coor/x",60);
  set("coor/y",90);
   set("coor/z",50);
   setup();
}

