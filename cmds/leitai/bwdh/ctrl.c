// ������ ctrl.c
// By River 99/04/15
// Modified by Numa 1999-11-25
// Modifier : Numa@Sj 2000.5.4

#define SAFE_PLACE "/cmds/leitai/bwdh/xiuxishi3.c"
#define NUMBER 3

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short",HIW"����̨"NOR);
        set("long", @LONG
�������齣��ӱ�������ʦ�����ң����ܿ����ڶ���ʦ����ææ���ڸ�Щ
ʲô�����������һ�źܴ�Ŀ���̨�������ʾ��һ�Ű�ť����Ϊ���Ե���һ
����ɫ�İ�ť��anniu)����֪������ȥ��ʲô������Ա߻���һ����ʾ(sign)��
LONG
        );

        set("exits", ([
                "down" : "/d/wizard/wizard_meet",
        ]));
        set("item_desc",([
                "sign" : "ָ��ʹ��˵����
                
                login    : ��¼������Ա��Ϣ��
                list     : ��ʾ������Ա��Ϣ��
                correct  : �޸ı�����Ա��Ϣ��
                send     : �������������Աȥɽׯ��
                set_item : ����ɽׯ��������Ʒ��
                press    : �򿪴��ţ���ʼ���䡣
                
                                ----Numa@Sj 2000-5-4\n",
        ]));
        set("objects",([
                __DIR__"obj/snooper1" : 1,
                __DIR__"obj/snooper2" : 1,
                __DIR__"obj/snooper3" : 1,
                __DIR__"obj/snooper4" : 1,
                __DIR__"obj/snooper5" : 1,
                __DIR__"obj/snooper6" : 1,
        ]));
        set("no_fight",1);
        set("ceshi",1);
        set("line",0);
        set("no_clean_up",1);
        setup();
}

void init()
{
        add_action("do_push", "press");
        add_action("do_login", "login");
        add_action("do_correct", "correct");
        add_action("do_list", ({"list","show"}));
        add_action("do_send", ({"send"}));
        add_action("do_set_item",({"set_item"}));
}

int do_set_item(string arg)
{
        object ob = this_object();
        
        if (!arg)
                return notify_fail("��ʽ��set_item no|yes\n\nset_item no : ɽׯ��������Ʒ����ʧ��\nset_item yes : ɽׯ��������Ʒ�Դ��ڡ�\n");
        if (arg == "no")
                ob->set("bw/set_item","no");
        else if (arg == "yes")
                ob->set("bw/set_item","yes");
        else
                return notify_fail("��ʽ��set_item no|yes\n\nset_item no : ɽׯ��������Ʒ����ʧ��\nset_item yes : ɽׯ��������Ʒ�Դ��ڡ�\n");
        tell_object(this_player(),"ɽׯ��������Ʒ����������Ϊ��"+arg=="no"?"��ʧ":"����"+"��\n");
        return 1;
}

int do_login(string arg)
{
        object ob = this_object();
        object me = this_player();
        string *group, pl0, pl1, pl2, pl3, msg;
        string re1, re2, re3;
        int i, j, number;

        if( wiz_level(me) < 3 )
                return notify_fail("ֻ�� (wizard) ���ϵ���ʦ��������̨login����player��\n");        


        number = NUMBER;
        
        if (!arg)
                return notify_fail("ָ���ʽ��login (�������) (��Աһ��Id) (��Ա����Id) ....\nע��Ŀǰÿ��Ϊ���"
                        + CHINESE_D->chinese_number(number) +"�ˡ�
                        
        ʾ��������һΪ ����һ�� ����ԱΪ id1, id2, id3
        ����д���ǲ����ã�
                login 1 ����һ�� id1 id2 id3
        ������������޷��μӣ����˴���Ļ�����id2�޷��μӣ�
        ��replace�����Ҵ��棬������Ϊ��
                login 1 ����һ�� id1(id1) id2(replace) id3(id3)
        
        �����Ϊ
                login 2 xxxxx xxx xxx xxx
        �������ơ�

                        \n");

        if (sscanf(arg, "%d %s",i, arg) != 2)
                return notify_fail("��Ҫ��ӵڼ��еı������ݣ�\n");
        
        if (!ob->query("packet"+(i-1)) && (i-1)!=0)
                return notify_fail("�밴��˳����д,��"+CHINESE_D->chinese_number(i-1)+"���������ݡ�\n");
        
        if (stringp(ob->query("packet" + i))) {
                group = explode(ob->query("packet" + i)," ");
                return notify_fail("��"+CHINESE_D->chinese_number(i)+"���Ѿ���������"+group[1]+"("+group[2]+"����)��"+group[3]+"("+group[4]+"����)��("+group[5]+"("+group[6]+"����)����ɵ�"+group[0]+"��\n");
        }
        if (sscanf(arg, "%s %s %s %s", pl0, pl1, pl2, pl3) != 4)
                return notify_fail("ָ���ʽ��login (�������) (��Աһ��Id) (��Ա����Id) ....\nע��Ŀǰÿ��Ϊ���"
                        + CHINESE_D->chinese_number(number) +"�ˡ�
                        
        ʾ��������һΪ ����һ�� ����ԱΪ id1, id2, id3
        ����д���ǲ����ã�
                login 1 ����һ�� id1 id2 id3
        ������������޷��μӣ����˴���Ļ�����id2�޷��μӣ�
        ��replace�����Ҵ��棬������Ϊ��
                login 1 ����һ�� id1(id1) id2(replace) id3(id3)
        
        �����Ϊ
                login 2 xxxxx xxx xxx xxx
        �������ơ�

                        \n");
        if (!ob->query("packet1")) {
                if (query("ceshi"))
                        tell_object(me,HIY"\n��ͨ�桿"+me->name(1)+"���������������ڿ�ʼ������ұ������ݣ�������Ժ\n\n"NOR);
                else
                        message("channel:chat",HIY"\n��ͨ�桿"+me->name(1)+"���������������ڿ�ʼ������ұ������ݣ�������Ժ\n\n"NOR,users());
        }
        ob->add("line",1);
        
                if (sscanf(pl1,"%s(%s)",pl1,re1)==2
                &&  sscanf(pl2,"%s(%s)",pl2,re2)==2
                &&  sscanf(pl3,"%s(%s)",pl3,re3)==2)
                        ob->set_temp("replace"+i,1);
                if (!ob->query_temp("replace"+i)) {
                        if (re1="0")
                                re1 = "��";
                        if (re2="0")
                                re2 = "��";
                        if (re3="0")
                                re3 = "��";
                }
                ob->set("packet"+i,pl0+" "+pl1+" "+re1+" "+pl2+" "+re2+" "+pl3+" "+re3);
                msg = "�����飺"+pl0+"�����������д��ϡ�\n";
                msg += "Ŀǰ����¼�ı��������������У�\n";
                msg += "���  ����      ��һλ    ������      �ڶ�λ    ������      ����λ    ������      \n";
                msg += "-------------------------------------------------------------------------------------\n";
                for (j=i;j>0;j--) {
                        group = explode(ob->query("packet"+j)," ");
                        if (sizeof(group)!=7) {
                                write("�쳣����������groupֻ��"+sizeof(group)+"�\n");
                                ob->delete("packet"+i);
                                return 1;
                        }
                        pl0 = group[0];
                        pl1 = group[1];
                        re1 = group[2];
                        pl2 = group[3];
                        re2 = group[4];
                        pl3 = group[5];
                        re3 = group[6];
                        msg += sprintf("%-6d%-10s%-10s��%-10s%-10s��%-10s%-10s��%-10s\n",j,pl0,pl1,re1,pl2,re2,pl3,re3);
                        continue;
                }
                msg += "-------------------------------------------------------------------------------------\n";
                msg += "\n�����������������correct (����)�����޸ģ����µ�¼��\n";
                tell_object(me,msg);
                                
                return 1;
}

int do_correct(string arg)
{
        object ob = this_object();
        object me = this_player();
        int i;

        if( wiz_level(me) < 3 )
                return notify_fail("ֻ�� (wizard) ���ϵ���ʦ��������̨ɾ����¼��\n");

        if (!arg)
                return notify_fail("������correct line (����)�����޸ġ�\n");
        if (sscanf(arg,"line %d",i)!=1)
                return notify_fail("������correct line (����)�����޸ġ�\n");
        if (!ob->query("packet"+i))
                return notify_fail("���в�û���κ�������ݡ�\n");
        
        tell_object(me,"��ȡ�����ļ��С������ɹ���ȡ��"+CHINESE_D->chinese_number(i)+"�У�\n");
        tell_object(me,ob->query("packet"+i));
        tell_object(me,"�����������޸ĵ����ݣ�\n");
        tell_object(me,"��ʽ��\n          ����һ�� id1(id1) id2(replace) id3(id3)\n�����룺......>");
        input_to("get_msg", ob, i);
        return 1;
}

int get_msg(string msg, object ob, int i)
{
        string pl0,pl1,pl2,pl3;
        string re1,re2,re3;
        
        if (sscanf(msg,"%s %s(%s) %s(%s) %s(%s)",pl0,pl1,re1,pl2,re2,pl3,re3)!=7) {
                write("���ݸ�ʽ����ӦΪ�� ����һ�� id1(id1) id2(id2) id3(id3)\n����������......>");
                input_to("get_msg", ob, i);
                return 1;
        }
        ob->set("packet"+i,pl0+" "+pl1+" "+re1+" "+pl2+" "+re2+" "+pl3+" "+re3);
        write("��"+CHINESE_D->chinese_number(i)+"�������޸���ϣ�����list�鿴��\n");
        return 1;
}

int do_list(string arg)
{
        object ob = this_object();
        object me = this_player();
        string *group, msg;
        string pl0, pl1, pl2, pl3;
        string re1, re2, re3;
        int i, j;
        
        if (!ob->query("packet1") || ob->query("line")==0)
                return notify_fail("��û����������������أ���\n");
        
        i = ob->query("line");
        msg = "Ŀǰ����¼�ı��������������У�\n";
        msg += "���  ����      ��һλ    ������      �ڶ�λ    ������      ����λ    ������      \n";
        msg += "-------------------------------------------------------------------------------------\n";
        for (j=i;j>0;j--) {
                group = explode(ob->query("packet"+j)," ");
                pl0 = group[0];
                pl1 = group[1];
                re1 = group[2];
                pl2 = group[3];
                re2 = group[4];
                pl3 = group[5];
                re3 = group[6];
                msg += sprintf("%-6d%-10s%-10s��%-10s%-10s��%-10s%-10s��%-10s\n",j,pl0,pl1,re1,pl2,re2,pl3,re3);
                continue;
        }
        msg += "-------------------------------------------------------------------------------------\n\n";
        if (!arg)
                tell_object(me,msg);
        else if (arg == "all")
                message("channel:chat",HIY"������ͨ�桿\n" + msg + "\n"NOR,users());
        else return notify_fail("��Ҫ��˭���������ݣ�(�޲������Լ���������Ϊallʱ��������ҿ�)\n");
        return 1;
}

// �滻���
object replace_player(string old, object ob)
{
        object user;
//        string temp
//      if(ob->query_temp("leitai"))
//              return notify_fail(ob->name()+"���ڱ����̨�����С�\n");
        seteuid(old);
        user = new("/cmds/leitai/leitaiuser");   // ȥ����save()����̨�е�һ�кͱ����޹ء�
        user->set_name("", ({ old }));
        if(!user->restore()) {
                destruct(user);
                return ob;
        }
        ob->move(SAFE_PLACE);
        user->setup();          
        user->set_temp("leitai", 1);    
        exec(user, ob);
        user->set("link_ob", ob);
        user->set_temp("link_ob", ob->query_temp("link_ob"));
//      user->move(this_object());
        user->clear_condition();
        user->reincarnate();
//      user->set("channels", ({ "rumor", "err" }) );
      tell_object(user, YEL"�����"+user->name()+"������̨��Ŀǰ�������״̬�С�\n"NOR"
��Ҫ���������Ʒ������ "YEL"NA"NOR" ��
�����׼���������"YEL" OK "NOR"��\n\n");
        if (old == ob->query("id") )
                user->set_temp("replace_msg",ob->query("name")+"("+ob->query("id")+")");
        else
                user->set_temp("replace_msg", ob->query("name")+"("+ob->query("id")+")����"+user->name()+"("+old+")");
        return user;
}

// �������
int resolve_player(object me, object ob, int num, int point)
{
        object *o = ({me,me,me});
        string *ms = ({" "," "," "}), *group;
        object gm1, gm2, gm3, room;
        string pl0, pl1, pl2, pl3;
        string re1, re2, re3;
        string msg = "", place;
        int i, where;

        if (point == 0) {
                place = "xiuxishi1";
                where = 1;
        }
        if (point == 1) {
                place = "xiuxishi2";
                where = 2;
        }
        
        if (!ob->query_temp("replace"+num)) {
                group = explode(ob->query("packet"+num)," ");
                pl0 = group[0];
                pl1 = group[1];
                pl2 = group[3];
                pl3 = group[5];
                if (!(gm1 = find_player(pl1)))
                        return notify_fail(pl1+"��������Ϸ�У��޷��μӣ����������������\n");
                if (!(gm2 = find_player(pl2)))
                        return notify_fail(pl2+"��������Ϸ�У��޷��μӣ����������������\n");
                if (!(gm3 = find_player(pl3)))
                        return notify_fail(pl3+"��������Ϸ�У��޷��μӣ����������������\n");

                        if (!(room = load_object(__DIR__ + place)))
                                return notify_fail("ERROR!!!ROOM " + place+" NOT EXISTS! \n");
                        room->set("party",pl0);
                        room->set("packet",pl1 + " " + pl2 + " " + pl3 + " ");
                        ob->set_temp("pp"+where,pl0);
                        ob->set_temp("p" + where + "/i1",pl1);
                        ob->set_temp("p" + where + "/i2",pl2);
                        ob->set_temp("p" + where + "/i3",pl3);
                        
                        gm1 = replace_player(pl1, gm1);
                        tell_room(environment(gm1),gm1->name(1)+"����ʮ���������Ϣ�ҡ�\n");
                        gm1->move(__DIR__ + place);
                        gm1->set_temp("leitai", 1);
                        tell_room(environment(gm1),HIY+gm1->name(1)+"���³������˹�����\n"NOR);
                        gm2 = replace_player(pl2, gm2);
                        tell_room(environment(gm2),gm2->name(2)+"����ʮ���������Ϣ�ҡ�\n");
                        gm2->move(__DIR__ + place);
                        gm2->set_temp("leitai", 1);
                        tell_room(environment(gm2),HIY+gm2->name(2)+"���³������˹�����\n"NOR);
                        gm3 = replace_player(pl3, gm3);
                        tell_room(environment(gm3),gm3->name(3)+"����ʮ���������Ϣ�ҡ�\n");
                        gm3->move(__DIR__ + place);
                        gm3->set_temp("leitai", 1);
                        tell_room(environment(gm3),HIY+gm3->name(3)+"���³������˹�����\n"NOR);
			if (query("ceshi"))
				tell_object(me, HIY"������ͨ�桿 ��"+CHINESE_D->chinese_number(num)+"�ӡ�"+pl0+"����"
                                	+gm1->name(1)+"("+gm1->query("id")+")��"
                			+gm2->name(1)+"("+gm2->query("id")+")��"
                			+gm3->name(1)+"("+gm3->query("id")+")��
                                	�Ѿ������Խ�ɽׯ��Ϣ�ң�׼����������ʱ���Կ�ʼ���䡣\n");
                        else
                        	message("channel:chat",HIY"������ͨ�桿 ��"+CHINESE_D->chinese_number(num)+"�ӡ�"+pl0+"����"
                                	+gm1->name(1)+"("+gm1->query("id")+")��"
                			+gm2->name(1)+"("+gm2->query("id")+")��"
                			+gm3->name(1)+"("+gm3->query("id")+")��
                                	�Ѿ������Խ�ɽׯ��Ϣ�ң�׼����������ʱ���Կ�ʼ���䡣\n",users());
//              }
                return 1;
        }
        else {
                group = explode(ob->query("packet"+num)," ");
                pl0 = group[0];
                pl1 = group[1];
                re1 = group[2];
                pl2 = group[3];
                re2 = group[4];
                pl3 = group[5];
                re3 = group[6];
                if (re1 == "��")
                        re1 = pl1;
                if (re2 == "��")
                        re2 = pl2;
                if (re3 == "��")
                        re3 = pl2;
                if (!(gm1 = find_player(re1)))
                        return notify_fail(re1+"��������Ϸ�У��޷��μӣ����������������\n");
                if (!(gm2 = find_player(re2)))
                        return notify_fail(re2+"��������Ϸ�У��޷��μӣ����������������\n");
                if (!(gm3 = find_player(re3)))
                        return notify_fail(re3+"��������Ϸ�У��޷��μӣ����������������\n");
                ms[0] = pl1;
                ms[1] = pl2;
                ms[2] = pl3;
                o[0] = gm1;
                o[1] = gm2;
                o[2] = gm3;
                if (!(room = load_object(__DIR__ + place)))
                        return notify_fail("ERROR!!!ROOM " + place+" NOT EXISTS! \n");
                room->set("packet",re1 + " " + re2 + " " + re3 + " ");
                room->set("party",pl0);
                ob->set_temp("pp" + where,pl0);
                ob->set_temp("p" + where + "/i1",pl1 +"("+re1+"����)");
                ob->set_temp("p" + where + "/i2",pl2 +"("+re2+"����)");
                ob->set_temp("p" + where + "/i3",pl3 +"("+re3+"����)");
                
                for (i=0;i<3;i++) {
                        o[i] = replace_player(ms[i], o[i]);
                        tell_room(environment(o[i]),o[i]->name(1)+"���³��Ĳ����Խ�ɽׯ��׼���μӱ��䡣\n");
                        o[i]->move(__DIR__ + place);
                        o[i]->set_temp("leitai",1);
                        tell_room(environment(o[i]),HIY+o[i]->name(1)+"���³������˹�����Ħȭ���ƣ�ԾԾ���ԡ�\n"NOR);
                        msg += o[i]->query_temp("replace_msg");
                        continue;
                }
                if (query("ceshi"))
                	tell_object(me,HIY"������ͨ�桿 ��"+CHINESE_D->chinese_number(num)+"�ӡ�"+pl0+"����"+msg+
                                "�Ѿ������Խ�ɽׯ��Ϣ�ң�׼����������ʱ���Կ�ʼ���䡣\n");
                else
                	message("channel:chat",HIY"������ͨ�桿 ��"+CHINESE_D->chinese_number(num)+"�ӡ�"+pl0+"����"+msg+
                                "�Ѿ������Խ�ɽׯ��Ϣ�ң�׼����������ʱ���Կ�ʼ���䡣\n",users());
                return 1;
        }

}

int do_send(string arg)
{
        object me = this_player();
        object ob = this_object();
        int num1, num2;
        
        if (!arg)
                return notify_fail("ָ���ʽ��send (�ڼ���) with (�ڼ���)\n");
        
        if (sscanf(arg,"%d with %d",num1,num2)!=2)
                return notify_fail("ָ���ʽ��send (�ڼ���) with (�ڼ���)\n");
        if (!ob->query("packet"+num1))
                return notify_fail("���ﲢû�е�"+CHINESE_D->chinese_number(num1)+"�ӡ�\n");
        if (!ob->query("packet"+num2))
                return notify_fail("���ﲢû�е�"+CHINESE_D->chinese_number(num2)+"�ӡ�\n");
                
        if (resolve_player(me, ob, num1, 0))
                tell_object(me,"���͵�"+CHINESE_D->chinese_number(num1)+"�ɹ���\n");
        else
                tell_object(me,"���͵�"+CHINESE_D->chinese_number(num1)+"ʧ�ܣ�\n");
        if (resolve_player(me, ob, num2, 1))
                tell_object(me,"���͵�"+CHINESE_D->chinese_number(num2)+"�ɹ���\n");
        else
                tell_object(me,"���͵�"+CHINESE_D->chinese_number(num2)+"ʧ�ܣ�\n");
        return 1;
}

void check_trigger()
{
       object room;
       object thisroom = this_object();
       if(!(room = find_object(__DIR__"xiuxishi2")))
             room = load_object(__DIR__"xiuxishi2");
       if( room = find_object(__DIR__"xiuxishi2")){
         if( !room->query("exits/enter")){
                 room->set("exits/enter", __DIR__"gate");                 
                 message("vision", HIR"ֻ������Ȼһ�����Խ�ɽׯ����Ϣ�ҵĴ��ű����ˡ�\n"NOR, thisroom);
                 message("vision", HIW"ֻ������֨һ������Ϣ�ҵĴ��ű����ˣ������ͨ���Խ�ɽׯ�ˡ�\n"NOR, room);
                 remove_call_out("close");
                 call_out("close", 100); 
                 }
                else message("vision", HIW"�Խ�ɽׯ����Ϣ�ҵĴ����Ѿ������ˣ��ٰ�Ҳû�����ˡ�\n"NOR, thisroom);
           } 
          else message("vision", "ERROR: Room 2 not found\n", thisroom);          
}

void check_trigger1()
{
       object room1;
       object thisroom = this_object();
       if(!(room1 = find_object(__DIR__"xiuxishi1")))
             room1 = load_object(__DIR__"xiuxishi1");
       if( room1 = find_object(__DIR__"xiuxishi1")){
         if( !room1->query("exits/enter")){                 
                 room1->set("exits/enter",__DIR__"houting");
                 message("vision", HIR"ֻ������Ȼһ�����Խ�ɽׯ����Ϣ�ҵĴ��ű����ˡ�\n"NOR, thisroom);
                 message("vision", HIW"ֻ������֨һ������Ϣ�ҵĴ��ű����ˣ������ͨ���Խ�ɽׯ�ˡ�\n"NOR, room1);
                 remove_call_out("close1");
                 call_out("close1", 100); 
                 }
                else message("vision", HIW"�Խ�ɽׯ����Ϣ�ҵĴ����Ѿ������ˣ��ٰ�Ҳû�����ˡ�\n"NOR, thisroom);
           } 
          else message("vision", "ERROR: Room 1 not found\n", thisroom);          
}

void close()
{
        object room;
        if( room = find_object(__DIR__"xiuxishi2"))
        room->delete("exits/enter");        
        message("vision", HIW"ֻ������֨һ������Ϣ�ҵĴ����ֱ������ˡ�\n"NOR, room);
}

void close1()
{
        object room1;
        if( room1 = find_object(__DIR__"xiuxishi1"))
        room1->delete("exits/enter");
        message("vision", HIW"ֻ������֨һ������Ϣ�ҵĴ����ֱ������ˡ�\n"NOR, room1);
}

int do_push(string arg)
{
       	object me = this_player();
       	object ob = this_object();
       
       	if (userp(me) && !wiz_level(me))
          	return notify_fail("�㲻����ʦ����Ҫ����Ҷ�����������ⲻ��Ŷ��\n");
       	if (!arg || arg !="anniu")
          	return notify_fail("��Ҫ��ʲô��\n");
       	if (arg == "anniu"){
           	message_vision(HIR"$N�������˿���������ʳָ�����ذ����˰�ť��\n"NOR, me);
           	if (query("ceshi"))
           		tell_object(me, "������ͨ�桿��"+ob->query_temp("pp1")+"���͡�"+ob->query_temp("pp2")+"��������ʽ��ʼ���䡣\n\n\t��"+ob->query_temp("pp1")+"����Ա��"+ob->query_temp("p1/i1")+"��"+ob->query_temp("p1/i2")+"��"+ob->query_temp("p1/i3")+"��\n\t��"+ob->query_temp("pp2")+"����Ա��"+ob->query_temp("p2/i1")+"��"+ob->query_temp("p2/i2")+"��"+ob->query_temp("p2/i3")+"��\n");
           	else
           		message("channel:chat","������ͨ�桿��"+ob->query_temp("pp1")+"���͡�"+ob->query_temp("pp2")+"��������ʽ��ʼ���䡣\n\n\t��"+ob->query_temp("pp1")+"����Ա��"+ob->query_temp("p1/i1")+"��"+ob->query_temp("p1/i2")+"��"+ob->query_temp("p1/i3")+"��\n\t��"+ob->query_temp("pp2")+"����Ա��"+ob->query_temp("p2/i1")+"��"+ob->query_temp("p2/i2")+"��"+ob->query_temp("p2/i3")+"��\n",users());
           	check_trigger();
           	check_trigger1();
           	return 1;
	} 
        return notify_fail("��Ҫ��ʲô��\n");
}
