// /d/xiangyang/xuanwumen.c

inherit ROOM;

string look_gaoshi();

void create()
{
        set("short", "������");
        set("long", @LONG
�����Ǿ������������ǵı��ţ���ʱ���ж�����׵�ʿ��������ȥ����
���Խ������������Ͼ��ڣ�����ȥ�ι��������䵱ɽ�����ŵ�ǽ��������һֽ
��ʾ(gaoshi)��
LONG
        );
        set("outdoors", "����");

        set("item_desc", ([
                "gaoshi" : (:look_gaoshi:),
        ]));
        set("objects", ([
            "/d/xiangyang/npc/guo" : 1,
                "/d/xiangyang/npc/dizi" : 3,
        ]));

        set("exits", ([
                "north" : __DIR__"outnroad1",
                "south" : __DIR__"nroad1",
        ]));

   set("coor/x",20);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",20);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",20);
  set("coor/y",0);
   set("coor/z",0);
   setup();
}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n��������ʹ\n���ĵ�\n";
}

int valid_leave(object me, string dir)
{
        if (dir == "north" || dir == "south")
        if ((me->query("family/family_name")!="������")&&(me->query_temp("xy/job"))&&(present("bing", this_object())))
                      return notify_fail("�ú��سǣ������ܡ�\n");
      return ::valid_leave(me, dir);
}


