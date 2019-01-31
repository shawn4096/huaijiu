// NPC: /d/huashan/npc/linghuchong.c
// Date: Look 99/03/25
// Modified by Numa@JH 2000 For ��ľ��Job

inherit NPC;
//inherit F_MASTER;

#include <ansi.h>
#include "skill1.h"

string ask_chongling();
string ask_ylj1();
string ask_ylj2();
string ask_ylj3();
int ask_ryy();
int ask_heimu();
int ask_follow();

void create()
{
        set_name("�����", ({ "linghu chong", "linghu", "chong" }));
        set("nickname", "��ʦ��");
        set("long", 
"�����Ľ��ݣ�����Ũü���ۣ������Ѱ�������\n"
"ͬ���������ϴ��ǻ�ɽ������һ���еĶ�����֡�\n"
"�������������Ⱥ���ڣ�������ִ���ճ����\n");
        set("gender", "����");
        set("age", 28);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 30);
        set("int", 40);
        set("con", 30);
        set("dex", 30);
        set("unique", 1);
        
        set("max_qi", 3000);
        set("max_jing", 1800);
        set("neili", 4000);
        set("max_neili", 4000);
        set("eff_jingli", 1800);

        set("jiali", 60);
        set("combat_exp", 800000);
        set("score", 8000);
        set("startroom","/d/huashan/siguoya");

        set_skill("blade", 120);
        set_skill("cuff", 120);
        set_skill("strike",120);
        set_skill("force", 120);
        set_skill("dodge", 120);
        set_skill("parry", 120);
        set_skill("sword", 120);
        set_skill("dugu-jiujian", 120);
        set_skill("zixia-gong", 120);
        set_skill("poyu-quan", 120);
        set_skill("fanliangyi-dao", 120);
        set_skill("hunyuan-zhang", 120);
        set_skill("huashan-jianfa", 120);
        set_skill("huashan-shenfa",120);
        set_skill("zhengqi-jue", 120);
        set_skill("chongling-jian", 120);

        map_skill("force", "zixia-gong");
        map_skill("cuff", "poyu-quan");
        map_skill("blade", "fanliangyi-dao");
        map_skill("strike", "hunyuan-zhang");
        map_skill("dodge", "huashan-shenfa");
        map_skill("parry", "huashan-jianfa");
        map_skill("sword", "huashan-jianfa");

        prepare_skill("cuff", "poyu-quan");

        create_family("��ɽ��", 14, "����");
        set("chat_msg_combat", ({
                (: random_move :)
        }) );
        set("chat_chance", 15);
        set("chat_msg", ({
                (: random_move :)
        }) );

        set("inquiry", ([
                "������" : "�����Ѿ��ܾ�û�м��������˼��ˡ���������\n",
                "����ɺ" : "����Сʦ����ʲô�°���\n",
                "����" : "������ã���ı���\n",
                "����" : (: ask_ylj3 :),
                "ī������" : (: ask_ylj2 :),
                "���齣��" : (: ask_chongling :),
                "������ã���ı���" : (: ask_ylj1 :),
// add here for ask
                "��ӯӯ" : (: ask_ryy :),
                "��ľ��" : (: ask_heimu :),
                "follow" : (: ask_follow :),
        ]));
        setup();
        carry_object(BINGQI_D("sword/sword"))->wield();
        carry_object(ARMOR_D("armor/cloth"))->wear();
}

string ask_chongling()
{
        mapping fam;
        object me;
        me = this_player();
        fam = me->query("family");
        if (!fam || fam["family_name"] !="��ɽ��")
           return RANK_D->query_respect(me)+"�뱾��������������֪�˻��Ӻ�̸��\n";
         if (! me->query("hs/getchongling"))
                return "���齣���������Һ�Сʦ���ڳ������轣ʱ��������";
        if((int)me->query_skill("chongling-jian", 1) > 60 )
           return "���齣�����ڶ������㻹���Լ�����ȥ�ɡ�\n";
        if( (int)me->query("jingli", 1) < 100 )
           return "����������״��̫���ˣ����޷�������齣���ľ���֮����\n";
        if( (int)me->query("jing", 1) < 100 )
           return "����������״��̫���ˣ����޷�������齣���ľ���֮����\n";
        me->improve_skill("chongling-jian", 20);
         me->receive_damage("jingli",30);
        me->receive_damage("jing", 30);
         me->start_busy(3);
        tell_object(me, HIC"�㲻���������������Ȼ��ţ��Խ���������������һ�㡣\n"NOR);
        return  "�ðɣ���Ȼ�������ҳ��齣�����Ҿ͸�����һ�Ρ�\n" ;
}

string ask_ylj1()
{
        object me;
        me = this_player();
        command("haha "+me->query("id"));
        me->set_temp("ylj/step1",1);
        return "��̨Ҳ֪������£����ǵ����ֵ���Ϊ�Ⱥ�ɽ�ɵ�����ʦ\n
�ã���ɻ�����ﲮ�⿪����Ц���º��ɽ�Ķ���ʦ������û���ң���������\n
һ�������Ѿ�����ī��������Ҫ����������һ�Ѿ�����������������Ц����\n
��.....\n";
}

string ask_ylj2()
{
        object me;
        me = this_player();
        if( !me->query_temp("ylj/step1") )
                return "����Ǹ��������ܡ�\n";
        me->set_temp("ylj/step2",1);
        me->delete_temp("ylj/step1");
        return "˵����ī������Ҳ��һ�������һֱ�Ҳ���������ʦ��\n
�����˷����������...��\n";
}

string ask_ylj3()
{
        object me, obj;
        me = this_player();
        if ( !me->query_temp("ylj/step2") )
                return "����Ǹ��������ܡ�\n";
        me->delete_temp("ylj/step2");
        command("look "+me->query("id"));
        if ( (int)me->query("shen") > 100000 )
        {
                obj = unew(__DIR__"obj/xuantie");
                if( clonep(obj) ) {
                        obj->move(me);
                        me->set_temp("ylj/step3",1);
                        return "����̨һ�����������������������̨������̨���ҵ���\n
����ʦ�����ɱ���������������Ҳ�����Ѷ���ʦ����һ������.....\n";
                }
        }
        return "����Ǹ��������ܡ�\n";
}

int ask_ryy()
{
        object ob = this_player();
        
        if (ob->query_temp("hostage/job_1") != 2)
        {
                command("say �Һܾ�û�������ˣ�");
                command("sigh");
                return 1;
        }
        ob->set_temp("hostage/ask_ling",1);
        command("ah " + ob->query("id"));
        command("say �������������������ô���ˣ�");
        command("say ���ĺ�ľ�������������뻹�����ء�");
        return 1;
}


int ask_heimu()
{
        object ob = this_player();
        object me = this_object();
        
        if (!ob->query_temp("hostage/ask_ling"))
        {
                command("say "+RANK_D->query_respect(ob)+"�������²�����ô����ģ�");
                return 1;
        }

        command("say ��Ҫ��ľ��ٺ٣����������Ա��ԣ�Ӯ���Ҿ͸��㣡");
        ob->set_temp("hostage/pass_l",1);
        call_out("do_clone",1,me,ob);
        return 1;
}

int accept_fight(object ob)
{
        object me = this_object();
        
        if ((int)ob->query_temp("hostage/passed_l"))
        {
                command("say ���ǲ��Ǳ��Թ�����");
                return 0;
        }

        if (me->query("eff_qi") < me->query("max_qi")
        || me->query("qi") < me->query("eff_qi")
        || me->query("neili") < me->query("max_neili"))
        {
        	me->reincarnate();
                message_vision(CYN"$N��$n˵���һ�û����Ϣ�ã����һ����ɡ�\n"NOR, ob, me);
                return 0;
        }
        if (ob->query_temp("hostage/pass_l"))
        {
                message_vision(CYN"$N��$n˵���ðɣ����Ҿ�ͬ���д꼸�аɣ��㵽Ϊֹ��\n"NOR, ob, me);
                remove_call_out("checking");
                call_out("checking", 1, me, ob);
                ob->delete_temp("hostage/pass_l");
                return 1;
        }
        else return 0;
}

int checking(object me, object ob)
{
        int my_max_qi,his_max_qi;
        my_max_qi  = (int)me->query("max_qi");
        his_max_qi = (int)ob->query("max_qi");

        if ( !present(ob, environment()) )
                return 1; 
        if (( (int)me->query("qi")*100 / my_max_qi) <= 50 )
        {
                message_vision(CYN"$N��$n��ס����̾��"+RANK_D->query_respect(ob)+"��Ȼ�ù�������ȴ���ȥ��ӯӯ����ɡ�\n"NOR, me, ob);
                ob->set_temp("hostage/passed_l", 1);
                if (me->query("block_msg/all")>0) {
                        me->revive();
                }
                me->reincarnate();
                me->set_leader(ob);
                me->delete("chat_chance");
                me->set("location",1);
                me->set_temp("no_return",1);
                message_vision("$N��������$nһ���ж���\n"NOR, me, ob);
                return 1;
        }
        if (( (int)ob->query("qi")*100 / his_max_qi) < 50 )
        {
                message_vision(CYN"$N���˿�$n��˵������Ĺ���ϡ��ƽ������ô����ȥ����ӯӯ��\n"NOR, me,ob);
                message_vision("$N����ææ�뿪�ˡ�\n",me);
                ob->set_temp("hostage/passno_l", 1);
                me->move(__DIR__"siguoya");
                message_vision("$N����ææ���˹�����\n", me);
                return 1;
        }
        if (me->is_fighting())
        {
                call_out("checking",1, me, ob);
                return 1;
        }
        return 1;
}

int ask_follow()
{
        object ob = this_object();
        object me = this_player();

        if (!me->query_temp("hostage/passed_l"))
                return 0;
        message_vision(CYN"$n������Ц������$N˵�����Ǿ��߰ɣ�\n"NOR,me,ob);
        ob->set_leader(me);
        message_vision("$n��������$Nһ���ж���\n"NOR,me,ob);
        ob->delete("chat_chance");
        return 1;
}
