// wu.c by snowman@SJ ؤ���ⳤ��
// Modify by Looklove@SJ 2000/8/30
// Last change by Looklove add a log_file 2000/9/1

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

string ask_job(string arg);
string ask_fangqi();
string ask_gonglao(object who);

void create()
{
    set_name("�ⳤ��", ({"wu zhanglao", "wu", "zhanglao"}));
        set("title", "ؤ��Ŵ�����");
        set("gender", "����");
        set_max_encumbrance(1000000);
        set("age", 55);
        set("long", "����ؤ��������֮һ,��ʹһ�ѹ�ͷ����\n");
        set("attitude", "peaceful");
        set("no_get", "�ⳤ�϶������̫���ˡ�\n");
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);
        set("unique", 1);
        set("no_bark",1);
        set("apprentice",1);
        set("per", 21);
        set("max_qi", 1900);
        set("max_jing", 1400);
        set("eff_jingli", 1400);
        set("jiali", 100);
        set("combat_exp", 600000);
        
        set_skill("force", 120); // �����ڹ�
        set_skill("checking",120); 
        set_skill("huntian-qigong", 120); // ��������
        set_skill("dodge", 120); // ��������
        set_skill("xiaoyaoyou", 120); // ǧ������ 
        set_skill("parry", 120); // �����м�
        set_skill("blade", 120);
        set_skill("liuhe-daofa",120);
        set_skill("begging", 90);
        set_skill("suohou-shou",140);
        set_skill("hand",130);
        map_skill("blade","liuhe-daofa");       
        map_skill("force", "huntian-qigong");
        map_skill("dodge", "qianli-xingqi");
        map_skill("parry","liuhe-daofa");
        map_skill("hand","suohou-shou");
        prepare_skill("hand","suohou-shou");
        create_family("ؤ��", 18, "�Ŵ�����");

        set("inquiry", ([
                "ؤ��" : "����ؤ�������µ�һ��\n",
                "name" : "�����ⳤ�硣\n",
                "job"  : (: ask_job :),
                "����"  : (: ask_gonglao :),
                "������"  : (: ask_fangqi :),
                "fangqi"  : (: ask_fangqi :),
                "����"  : (: ask_fangqi :),
                "��������" : "�����ҵ�С���ӣ����𿼺����ĺú���\n",
        ]));
        setup();
        carry_object(BINGQI_D("blade"))->wield();
}

string ask_job(string arg)
{
        object player, me;
        mapping quest;
        
        player = this_player();
        me = this_object();
        
        player->start_busy(2);      
        if (!player->query("gb_pass"))
                return "��û��ͨ���������ӵĿ��飬�ҿɲ������㡣";         

        if(player->query("gb_job") > 10000)
                return "���Ѿ�Ϊ��ؤ�����������ô��Σ�����ʵ�ڲ����ķ��������ˡ�";

        if(player->query("combat_exp") > 6000000)
                return "������ô�ߵ����֣�Ҫ����������ʧ������ݣ��������˰ɡ�";

        if(player->query("job_name") =="ؤ��")
                return "�����ҿ�û�и�������񣬵Ȼ���ô����";

        if( player->query_temp("gb_wait_job") >= 5 ){
                command("say ������ǲ�����ţ�����Ȼ�����ǵȻ����");
                command("kick "+player->query("id"));
                tell_room(environment(), "\n�ⳤ�Ϸ���һ�ţ���"+ player->name()+ "�߷ɳ�ȥ��\n"NOR, ({ player }));
                player->move("/d/gb/yuchuan5");
                tell_room(environment(player), "\nֻ��"+ player->name()+ "���һ���ɹ�����ˤ�˸�����ʺ��\n"NOR, ({ player }));
                player->start_busy(6);
                player->delete_temp("gb_wait_job");
                return "������ľͷ���������˰���";
        }
        
        if( me->is_busy() ){
                player->add_temp("gb_wait_job", 1);
                return "û��������æ����,���һ�ᡣ";
        }

        if ((int)player->query_condition("gb_busy")){
                player->add_temp("gb_wait_job", 1);
                return "�����ϸ�����ȥ������ȥ�������ҽ��İɣ��Ȼ�������";
        }
        
        // now all jobs use this condition.
        if ((int)player->query_condition("job_busy")){
                if( player->query_temp("quest/id") && player->query_temp("quest/family") == "ؤ��")
                        return "��������ȥɱ"+player->query_temp("quest/name")+"������ô�������\n";
                if( player->query_temp("quest/family") == "ؤ��")
                        return "����������㻹û�����ô���ܻ����ˣ�";
                else
                        return "�����ҿ�û�и�������񣬵Ȼ������ɣ�";
         }
        
        if ((string)player->query_temp("quest/family") == "������"){
                player->add("gb_job", -player->query("gb_job")/10);
                player->delete_temp("quest");
                return "����ȥΪ���Ϲ�Ч�����۵������ؤ�����������һ�ɣ�"; 
        }

        if ((int)player->query_condition("guanfu_task"))
                return "���Ѿ�Ͷ���ٸ���ô���������������Ҫ�������ʲ�᣿";

        if ((int)player->query_condition("dali_songxi"))
                return "���Ѿ������������߾ͣ�����������Ѱʲô���ģ�";
      
        if(!mapp(quest= TASK_D->get_quest(player, 1, "ɱ", "ؤ��"))) 
                return "�����ҿ�û�и�������񣬵Ȼ���ô����"; 

        me->start_busy(2);
        player->delete_temp("gb_wait_job");
        player->set_temp("quest", quest);
        player->apply_condition("job_busy", 30+random(20));
        player->set_temp("gb_job", 1);
        player->set("job_name", "ؤ��");
        return "�ðɣ������"+quest["name"]+CYN"��һֱ����ؤ�����ԣ���ǰȥ�跨�����˳�����
            ����������"+quest["place"]+CYN"һ���������"+TASK_D->get_time(quest["time"])+"֮ǰ�ϻ�����\n";   
}

int accept_object(object who, object ob, object me)
{
        int type;
        me = this_object();

        if( me->is_busy() ){
                command("say ��������æ���أ����Ե�һ�°ɡ�");
                return 0;
        }
        if ( !who->query("gb_pass")) return 0;
        if ( !who->query_temp("gb_job")){
                command("say �Һ���û�и��������񰡣�");
                return 0;
        }
        if( ob->query("id")!="corpse" && ob->query("id")!="shouji") return 0;
                who->start_busy(1);
        
        if (who->query_temp("quest/family") == "������"){
                command("chat "+ who->name(1)+"͵͵Ϊ������Ч�������ڰ��������ؤ�\n");
                command("chat "+ who->name(1)+"������ְ��࣬���˵ö���֮!!!\n");
                who->delete("gb_pass");
                return 0; 
        }

        // check job.
        type = TASK_D->is_target(ob, who);
        
        switch (type){
            case 0: command("say �ⶫ����Ҫ��û�á�");
                    return 0;
            case -2:command("say �ٺ١���������ɱ�����ˡ�");
                    return 0;
            case -3:command("say �ţ���ô�òŰ��꣬���ʲôȥ�ˣ����ҹ�һ��ȥ��");
                    who->apply_condition("job_busy", 30);
                    return 0;
            case -4:command("say " + RANK_D->query_rude(who) + "����Ȼ����ƭ�����ϣ��������ѣ�");
                    call_out("killing_object",1, who);
                    return 0;
            default:call_out("destroy", 1, ob);
                    me->start_busy(2);
                    call_out("ok", 1, who);
                    return 1;
        }
        return 0;
}

void ok(object apper)
{
        int job_time,pot,exp;
        if (!apper) return;
        if ( apper->query("family/family_name") == "ؤ��"
          && apper->query_skill("huntian-qigong")){
            apper->improve_skill("huntian-qigong",apper->query("int")*2);
        }
        command("thumb " + apper->query("id"));
        command("say ��Ϊؤ�������˹��ͣ����Ǿ����������ġ�");
 
        job_time = (int)apper->query("gb_job")/800;
        if (job_time <1) job_time = 0;

        tell_room(environment(),HIY "�ⳤ����"+ apper->name()+ "�Ķ��ߵ����ƺ��ڽ�����ʲ�ᣬһ���"+ apper->name() +"��ס��ͷ�����ϲɫ��\n"NOR, ({ apper }));
        tell_object(apper, "�ⳤ�Ϸ��������������ָ������һЩ�书Ҫ��...\n");
        TASK_D->give_reward(apper, apper->query_temp("quest"), 1, job_time);

        apper->apply_condition("job_busy", 3+random(3));
        this_object()->start_busy(2);
        apper->add("gb_job",1); 
        apper->delete_temp("gb_job");      
        pot= apper->query_temp("quest/pot_reward");
        exp= apper->query_temp("quest/exp_reward");
        apper->delete_temp("quest");
        log_file( "job/gb_job",sprintf("%s %s(%s)��%d��ؤ������%d�㾭�飬%d��Ǳ�ܣ����飺%d\n",
        ctime(time())[4..19],apper->name(),apper->query("id"),apper->query("gb_job"),exp,pot,apper->query("combat_exp")));
        return;
}

void attempt_apprentice(object ob)
{
        if (ob->query("family/family_name")
        && ob->query("family/family_name") != "ؤ��") {
                command("say �㻹��ȥ������ɿ����ɡ�");
                return;
        }
        if ((int)ob->query("gb_bags") >= 2 
        && ob->query("family/family_name") != "ؤ��" ) {
                command("say ؤ����ݲ��������ֱ��������С�ˣ�");
                command("kill "+ob->query("id"));
                return;
        }

        command("say �ðɣ�ϣ��" + RANK_D->query_respect(ob) +
        "�ܺú�ѧϰ�����书�������ڽ����д���һ����Ϊ��");
        command("recruit " + ob->query("id"));
        if (ob->query("gb_bags")<1) ob->set("gb_bags", 1);
        ob->set("title",sprintf("ؤ����ŷֶ�%s������",
                chinese_number(ob->query("gb_bags"))) );
        ob->set("gb/fenduo","���ŷֶ�");
        ob->set("gb/alloted",1);
        ob->set("class","beggar");
}

void killing_object(object who)
{
        object me = this_object();
        if(!who || environment(who)!=environment(me)) return;
        me->kill_ob(who);
        who->unconcious();
}

string ask_fangqi()
{
        object me;
        int exp;

        me = this_player();
        exp = me->query("combat_exp");
        if(!me->query("gb_pass"))
              return "�����ؤ��Ӣ��,������Ϲ����ʲ��?";
        if(!me->query_temp("quest") || me->query_temp("quest/family") != "ؤ��")
              return "��û��������,������Ϲ����ʲ��?";
        if(me->query("gb_job") < 1 ){
              me->set("gb_job", 0);
              return "���û�кú���ɹ�����������Ϲ����ʲ�᣿";
        }
        me->delete_temp("gb_wait_job");
        me->clear_condition("job_busy");
        me->add("combat_exp",-(10+random(50)));
        if(exp>500000){
              me->add("combat_exp",-(10+random(40)));
        }
        me->start_busy(3);
        me->apply_condition("gb_busy",6+random(4));
        me->delete_temp("quest");
        me->delete_temp("gb_job");
        me->delete("job_name");
        me->add("gb_job",-1);
        return "��Ȼ��ɲ���Ҳû��ϵ,��ȥ�̿�������,�Ժ�����Ϊؤ�����!";
}

void destroy(object obj)
{
        if (obj) destruct(obj);
}

string ask_gonglao(object who)
{
        object me;
        int i;
             
        me = this_player();       
        if(!intp(i = me->query("gb_job")))
               return "��ûΪ��ؤ������κ�����������ʲô������?"; 

    message_vision("$N�ͳ�һ�����ӷ��˷���ָ�������ī����$n˵������Ŀǰ�Ѽǹ�" + chinese_number(i) + "�Ρ�\n",who,me);
        return "��ؤ�������ͷ�����������Ŭ���ɣ����ֽ����Ͳ����뻳�С�";
}
