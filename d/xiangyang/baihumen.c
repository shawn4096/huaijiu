// /d/xiangyang/baihumen.c

inherit ROOM;

string look_gaoshi();

void create()
{
        set("short", "�׻���");
        set("long", @LONG
�����Ǿ������������ǵ����ţ���ʱ���ж�����׵�ʿ��������ȥ������
�����������ս������˴�Ƭ�Ļĵأ�����ϡ�١����ŵ�ǽ��������һֽ��ʾ
(gaoshi)��
LONG
        );
        set("outdoors", "����");

        set("item_desc", ([
                "gaoshi" : (:look_gaoshi:),
        ]));

        set("objects", ([
//              "/d/xiangyang/npc/wuxiuwen" : 1,
                "/d/xiangyang/npc/wudunru" : 1,
                "/d/xiangyang/npc/wanyan" : 1,
                "/d/xiangyang/npc/yelvyan" : 1,
        ]));
        set("exits", ([
                "west" : __DIR__"outwroad1",
                "east" : __DIR__"bhnj",
        ]));

        setup();
}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n��������ʹ\n���ĵ�\n";
}

int valid_leave(object me, string dir)
{
        if (dir == "west" || dir == "east")
        if ((me->query("family/family_name")!="������")&&(me->query_temp("xy/job"))&&(present("bing", this_object())))
                      return notify_fail("�ú��سǣ������ܡ�\n");
        return ::valid_leave(me, dir);
}

