// /u/beyond/mr/npc/wang.c ������
// this is made by beyond
// update 1997.6.29
#include <ansi.h>

inherit NPC;
inherit F_MASTER;

string ask_job();
int ask_ok();

void create()
{
        set_name("������",({"wang furen","wang","furen"}));
        set("gender", "Ů��");
        set("rank_info/respect", "����");
        set("title","��٢��ɽׯ��");
        set("long", 
              "��������٢��ɽׯ�����ˣ�������ȥ������ʮ�мӣ��������ȴ档\n");
        set("age", 40);
        set("attitude", "friendly");
        set("no_bark",1);
        set("shen_type", 0);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        
        set("max_qi", 1500);
        set("max_jing", 1500);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 0);
        set("combat_exp", 180000);
        set("score", 15000);

        set_skill("dodge",100);
        set_skill("force", 100);
        set_skill("shenyuan-gong", 100);
        set_skill("yanling-shenfa", 100);
        set_skill("parry", 100);
        set_skill("murong-jianfa", 100);
        set_skill("literate", 100);
        set_skill("sword", 100);
        set_skill("finger", 100);
        set_skill("canhe-zhi", 100);
        set_skill("strike", 100);
        set_skill("xingyi-zhang", 100);
       // set_skill("beauty",300);
        
        map_skill("force", "shenyuan-gong");
        map_skill("dodge", "yanling-shenfa");
        map_skill("strike", "xingyi-zhang");
        map_skill("finger", "canhe-zhi");
        map_skill("parry", "murong-jianfa");
        map_skill("sword", "murong-jianfa");    
        prepare_skill("finger", "canhe-zhi");
        prepare_skill("strike", "xingyi-zhang");
        
        setup();
        carry_object(__DIR__"obj/shoe")->wear();
        carry_object(__DIR__"obj/red_silk")->wear();
        carry_object(__DIR__"obj/skirt")->wear();
        create_family("����Ľ��",3,"����");
        set("inquiry", ([
            "name" : "�Ҿ�����٢��ɽׯ�����ˣ��������ѵ�û��ʲô��ʾ��\n",
            "here" : "��������٢��ɽׯ��ׯԺ֮���ڣ��˴���Ϊ�ƽ�¥��\n",
            "rumors" : "������Ǳ���Ľ�ݲ����������ˡ�\n",
            "������" : "�������ҵı���Ů������ɱ�����������⡣\n",
            "Ľ�ݸ�" : "Ľ�ݸ������ǲ�������ֶ�����������Ա�֮����ʩ����ľ��������𽭺���\n",
            "������" : "������������٢��ɽׯ�Ĳ���֮����һ�����Ǳ����ȥ�ˡ�\n",
            "��٢��ɽׯ" : "���������٢��ɽׯ���Ҿ�����������ˡ�\n",
            "��ʩˮ��" : "���������������֮���ڣ�������ʩˮ��Ĳ����������Ƕ�Ķ�ѽ��\n",       
            "job" : (: ask_job :),
            "ok"  : (: ask_ok :),
       ]));
       
}

string ask_job()
{
        mapping fam;
        object me = this_player();
        
        if (!(fam = me->query("family")) || fam["family_name"] != "����Ľ��") // ������Ľ���ɵ���
               return RANK_D->query_respect(me) +
               "�뱾��������������֪�˻��Ӻ�̸��";

        if(me->query_condition("mrhua_job") > 0)
               return "���������ݣ����һ�������ɡ�\n";       
               
        if ((int)me->query("combat_exp") > 100000 )
               return "���Ժ������ˡ�";
               
        if (me->query_temp("mrhua")||me->query_temp("yanpopo"))
               return "�㲻���Ѿ����˹���ô��������ȥ����";
               
        me->set_temp("mrhua",1);
        me->set_temp("yanpopo",1);
        me->apply_condition("mrhua_job",random(5) + 6);
        
        return "ׯ�ſڵĲ軨������Ĳ�ʢ���úú�����һ���ˣ���ȥ�������ţ��������Űɡ�\n";
}

int ask_ok()
{
        object me = this_player();
        int exp, pot, gold;
        
        if(me->query_temp("mark/����")){                             
                exp = random(30)+me->query("max_pot")/2;
                pot = exp /5 +random(exp/6);          
                gold = (random(30)+15)*100;
                
	        if( (int)me->query_skill("literate", 1) < 30 || (int)me->query_skill("force", 1) < 40)
                    gold = (random(4)+2)*100;

                if(me->query_temp("killke"))
                    exp = exp + exp / 3;
                    
                me->add("potential",pot);
                me->add("combat_exp",exp);
                MONEY_D->pay_player(me, gold);
                
                if(me->query("potential") > me->query("max_pot"))
                    me->set("potential", me->query("max_pot"));
                
                tell_object(me,HIW"�㱻�����ˣ�\n" + 
                       chinese_number(exp) + "��ʵս����\n" +
                       chinese_number(pot) + "��Ǳ��\n"+
                         chinese_number(gold/100)+"��������\n"
                       NOR);      
                me->delete_temp("mark/����");
                me->delete_temp("mrhua");
                me->delete_temp("yanpopo");
                me->delete_temp("killke");      
                
                log_file("job/mrhua_job",
                  sprintf("%s %s(%s) Ľ���ֻ������ %d ���飬%d Ǳ�ܡ�\n",
                    ctime(time()),me->name(1), geteuid(me),exp,pot));
         }
         return 1;
}

void attempt_apprentice(object ob)
{
        command("say �ţ����㻹�Ǹ�ѧ����ϣ��Ҿ�������ɣ�");
        command("recruit " + ob->query("id"));
        ob->set("title","����Ľ�ݵ��Ĵ�����");
}
