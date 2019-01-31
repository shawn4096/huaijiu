#include <ansi.h>
inherit NPC;
#include "/d/xiangyang/npc/reward.h"

int ask_job();
int ask_job_gb();
void job_running_2();
int ask_job_time();
void job_running();
void job_starting();
void no_job();
int ask_finish();

void create()
{
        set_name("����", ({"guo jing", "guo", "jing"}));
        set("nickname", HIY"����"NOR);
        set("gender", "����");
        set("age", 40);
        set("long", "�������������µĴ����������ڶ��λ�ɽ�۽���ųơ���������\n");
        set("attitude", "friendly");
        set("str", 50);
        set("int", 10);
        set("con", 50);
        set("dex", 25);
        set("unique", 1);
        set("no_get", 1);

        set("max_qi", 9000);
        set("max_jing", 8000);
        set("neili", 18000);
        set("max_neili", 15000);
        set("jiali", 100);
        set("eff_jingli",9000);
        set("combat_exp", 3500000);

        set_skill("force", 300);
        set_skill("finger",300);
        set_skill("tanzhi-shentong",300);
        set_skill("yiyang-zhi",300);
        set_skill("claw",300);
        set_skill("jiuyin-baiguzhua",300);
        set_skill("huntian-qigong", 300);
        set_skill("strike", 300);
        set_skill("xianglong-zhang", 320);
        set_skill("dodge", 300);
        set_skill("jinyan-gong", 300);
        set_skill("parry", 300);

        map_skill("force", "huntian-qigong");
        map_skill("strike", "xianglong-zhang");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "xianglong-zhang");
        map_skill("finger","tanzhi-shentong");
        map_skill("claw", "jiuyin-baiguzhua");
        prepare_skill("strike", "xianglong-zhang");

        set("inquiry", ([
                "�س�": (: ask_job :),
                "����": (: ask_job_time :),
                "����": (: ask_job_gb :),
                "���": (: ask_finish :),
        ]) );

        set_temp("apply/damage",100);
        set_temp("apply/defence",100);
        set_temp("double_attack",1);

        set("start",1);
        set("thjob",3);
        set("gbjob",3);
        set("gmjob",3);
        set("emjob",3);
        set("job",7);
        set("finish",0);

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "strike.paiyun" :),
                (: perform_action, "strike.kanglong" :),
        }));
        create_family("ؤ��", 18, "�����״�����");
        setup();

        if (clonep()) carry_object("/d/thd/obj/grn-cloth.c")->wear();
}

void kill_ob(object me)
{
        if (userp(me)) me->apply_condition("kill_guo", 200);
        ::kill_ob(me);
}


void die()
{
        command("chat ��....�ض���������...һ���ˣ�");
        command("chat �������������....��....����.....");
        ::die();
}


int ask_job_time()
{
        object me = this_player();
        int i;
        if(!intp(i = me->query("xy/job")) || i <= 1 )
        {
                command("say �����û��æ�ɣ�");
                return 1;
        }
        message_vision("$N��$n˵�������Ѱ�æ�س�" + chinese_number(i) + "�Ρ�\n", this_object(), me);
        command("courage " + me->query("id"));
        return 1;
}


int ask_job()
{
        object me = this_player();
        object ob = this_object();
        object *list;
        list = filter_array(users(), (: $1->query("combat_exp")>10000 :));

        command("say ��˵�ɹŲ���Ӳ����׼�������ָ������������ǡ�");
        command("say ����������Ժ����æ������Ҫ���ĥ���Լ���");
        return 1;
        if (me->query("combat_exp")<800000)
        {
                command("say ��л���⣬�������������˵̫Σ���ˡ�");
                return 1;
        }

        if( me->query_condition("kill_guo") > 0 || me->query("menggu"))
        { 
               command("kick "+ me->query("id"));
               command("say ������������������سǣ�");
               command("kill "+ me->query("id"));
               return 1;
        }
        if (ob->query_temp("xy/nojob")||sizeof(list) > 100)
        {
                command("say �ɹű��ܵ��ش죬��ʱ���ṥ���ˡ�");
                command("say ����ļ�������ȥ��Ϣ�ɡ�");
                me->start_busy(5);
                return 1;
        }
        if (me->query_temp("xy/job"))
        {
                command("say ��ȥ���ָ���ص�ɡ�");
                command("push " + me->query("id"));
                return 1;
        }
        if (query("start")>0)
        {
                 command("chat �ɹű���Ҫ�����ˣ����λС�ģ�");
                 command("chat ����ɵ��˵ȣ��벻Ҫ�ӽ����ţ�");
        CHANNEL_D->do_channel(this_object(), "rumor", HBMAG+HIW"��˵�ɹű�Ҫ���������ˣ�");
                 set("start",0);
                 set("finish",0);
                 call_out("job_starting",120);
        }
        if ((me->query("family/family_name") == "�һ���")&&(query("thjob")>1))
        {
                command("say ԭ���������ĵ��ӣ��뵽���Ű����Ǳߵ��һ����ӡ�");
                command("say ����Ҫ�ڶ�������ǣ�Ƶ��ˣ����С�ġ�");
                me->set_temp("xy/job",1);
        me->apply_condition("guo_job",35);
                add("thjob",-1);
                return 1;
        }
        else if ((me->query("family/family_name") == "ؤ��")&&(query("gbjob")>1))
        {
                command("say ��ʦ����ͽ�ܣ���л����������������ҡ�");
                command("say �����Ǳ��ţ��׵��ɹű��Ĺ�������Ҫ��С�ġ�");
                me->set_temp("xy/job",1);
                me->apply_condition("guo_job",35);
                add("gbjob",-1);
                return 1;
        }
        else if ((me->query("family/family_name") == "������")&&(query("emjob")>1))
        {
                command("say ����СŮ���ĵ��ӣ��뵽�����İ�æ����");
                command("say �ǵ�����Ҫ����Ӧ�䣬���ҾȻ����ߡ�");
                command("say ���п��������з���������ҪС�ľ��䡣");
        me->set_temp("xy/job",1);
        me->apply_condition("guo_job",35);
                add("emjob", -1);
                return 1;
        }
        else  if ((me->query("family/family_name") == "��Ĺ��")&&(query("gmjob")>1))
        {
                command("say ԭ���ǹ����İ��֣��뵽���Ű�æ�ҵ�ͽ���ǡ�");
                command("say �����书��ǿ����ȥ�����������ˡ�");
                me->set_temp("xy/job",1);
                me->apply_condition("guo_job",20);
                add("gmjob",-1);
                return 1;
        }
        else if (query("job")>1)
        {
                command("say ��ô���뵽���Ű�æ�ҵ�Ů��Ů���ɡ�");
                command("say ��Ȼ����Զ��ս��������ҪС���ɹű�ͻȻ���֡�");
                me->set_temp("xy/job",1);
        me->apply_condition("guo_job",35);
                add("job",-1);
                return 1;
        }
        command("say ��л���⣬���������Ѿ��㹻�ˡ�");
        command("thank "+me->query("id"));
        return 1;
}


int ask_job_gb()
{
        object me = this_player();

        if(!me->query_temp("xy/job"))
        {
                  command("say ����Ҫ��æ�س�ô��");
                  return 1;
        }
        if (me->query("family/family_name") != "ؤ��")
        {
                  command("say ���ȥָ���ĵص�ɣ������ɹű���Ҫ�����ˣ�");
                  command("push");
                  return 1;
        }
        command("nod");
        command("say �����ٹ�һ���ɹű���Ҫ��ʼ�����ˣ����׼��һ�°ɡ�");
        me->set_temp("xy/job",2);
        return 1;
}

void job_starting()
{
        if (query("gbjob")+query("thjob")+query("emjob")+query("gmjob")<20) {
                command("chat �ɹű���ʼ�����ˣ���Һú���ס������");
                command("chat ����Ҳ�����˵о��ļ�ϸ����Ҳ�Ҫ������ţ�");
                call_out("job_running", 20);
                call_out("no_job", 1800+random(600));
                this_object()->set_temp("xy/nojob",1);
        } else {
                command("chat �ɹű��ƺ�ͻȻ��ȴ�ˣ����λ��Ϣһ�°ɡ�");
                set("start",1);
                set("finish",0);
                set_temp("xy/nojob",1);
                call_out("no_job", 600+random(120));
        }
}

void job_running()
{
        object ob, tmp, room = load_object("/d/xiangyang/qinglongmen");
        int i;

        set("start",1);
        set_temp("xy/nojob",1);
        ob = new("/d/xiangyang/npc/wushi");
        ob->move(room);
        if (tmp = present("cheng ying", room)) {
                ob->kill_ob(tmp);
                tmp->kill_ob(ob);
        }
        if (tmp = present("feng mofeng", room)) {
                ob->kill_ob(tmp);
                tmp->kill_ob(ob);
        }
        if (tmp = present("wu tianfeng", room)) {
                ob->kill_ob(tmp);
                tmp->kill_ob(ob);
        }
        for(i = 0; i < (7-query("thjob")); i++)
        {
                ob = new("/d/xiangyang/npc/bing");
                ob->move(room);
                if (tmp = present("cheng ying", room)) {
                        ob->kill_ob(tmp);
                        tmp->kill_ob(ob);
                }
                if (tmp = present("feng mofeng", room)) {
                        ob->kill_ob(tmp);
                        tmp->kill_ob(ob);
                }
                if (tmp = present("wu tianfeng", room)) {
                        ob->kill_ob(tmp);
                        tmp->kill_ob(ob);
                }
        }
        room = load_object("/d/xiangyang/xuanwumen");
        for(i = 0; i < (7-query("gbjob")); i++)
        {
                ob = new("/d/xiangyang/npc/wushi");
                ob->move(room);
                if (tmp = present("guo jing", room)) {
                        ob->kill_ob(tmp);
                        tmp->kill_ob(ob);
                }
                if (tmp = present("dizi", room)) {
                        ob->kill_ob(tmp);
                        tmp->kill_ob(ob);
                }
                if (tmp = present("dizi 2", room)) {
                        ob->kill_ob(tmp);
                        tmp->kill_ob(ob);
                }
                if (tmp = present("dizi 3", room)) {
                        ob->kill_ob(tmp);
                        tmp->kill_ob(ob);
                }
        }
        room = load_object("/d/xiangyang/baihumen");
        for(i = 0; i < (9-query("gmjob")); i++)
        {
                ob = new("/d/xiangyang/npc/bing");
                ob->move(room);
                ob->set("combat_exp",800000);
                if (tmp = present("wu xiuwen", room)) {
                        ob->kill_ob(tmp);
                        tmp->kill_ob(ob);
                }
                if (tmp = present("wu dunru", room)) {
                        ob->kill_ob(tmp);
                        tmp->kill_ob(ob);
                }
                if (tmp = present("wanyan ping", room)) {
                        ob->kill_ob(tmp);
                        tmp->kill_ob(ob);
                }
                if (tmp = present("yelv yan", room)) {
                        ob->kill_ob(tmp);
                        tmp->kill_ob(ob);
                }
        }
        room = load_object("/d/xiangyang/cross2");
        for(i = 0; i < (7-query("emjob")); i++)
        {
                ob = new("/d/xiangyang/npc/bing");
                ob->move(room);
                ob->set_name("��ϸ", ({ "spy" }));
                if (tmp = present("guo xiang", room)) {
                        ob->kill_ob(tmp);
                        tmp->kill_ob(ob);
                }
                if (tmp = present("dizi", room)) {
                        ob->kill_ob(tmp);
                        tmp->kill_ob(ob);
                }
                if (tmp = present("dizi 2", room)) {
                        ob->kill_ob(tmp);
                        tmp->kill_ob(ob);
                }
                if (tmp = present("dizi 3", room)) {
                        ob->kill_ob(tmp);
                        tmp->kill_ob(ob);
                }
        }
        call_out("job_running_2",120);
}

void job_running_2()
{
        object ob, tmp, room = load_object("/d/xiangyang/zhuquemen");
        int i;

        command("chat �ҷ��õ�����Ϣ��ȷ�����ų����˴�������");
        command("chat ���˰Ѹ����о���ʰ�����ٵ�����֧Ԯ��");
        for(i = 0; i < (10-query("job")); i++)
        {
                ob = new("/d/xiangyang/npc/wushi");
                ob->move(room);
                if (tmp = present("guo fu", room)) {
                        ob->kill_ob(tmp);
                        tmp->kill_ob(ob);
                }
                if (tmp = present("yelv qi", room)) {
                        ob->kill_ob(tmp);
                        tmp->kill_ob(ob);
                }
        }
        set("finish",1);
}

int ask_finish()
{
        object me = this_player();
        int exp, pot, nexp;

        if (me->query_temp("xy/job") < 3)
        {
                command("say ����û��ʲô����");
                command("kick " + me->query("id"));
                return 1;
        }
        if (query("finish")!=1)
        {
                command("say ����ս����������������˶���ɣ�");
                return 1;
        }
        command("admire " + me->query("id"));
        command("say ���´��������ǵİ��������л��");
        me->add("xy/job",1);
        exp=random(me->query("xy/job")/5 )+ (me->query_temp("xy/job")-2)*50 + 300 + random(200);
        if(exp > 1500) exp = 1300 + random(300);
        if (exp < 500) exp = 400 + random(100);
        message_vision("���������ǣ�"+exp+"\n",me);
        nexp = exp;
        exp = cal_exp(exp, me);
        pot = exp/6 +random(exp/10);
        me->add("combat_exp",exp);
        if(me->query("potential") + pot > me->query("max_pot"))
                me->set("potential", me->query("max_pot"));
        else me->add("potential", pot);
        message_vision(HIW"$N�����"+CHINESE_D->chinese_number(exp)+
                "�㾭�飬"+ CHINESE_D->chinese_number(pot)+
                "��Ǳ�ܵĽ�����\n"NOR, me);
        if (me->query("family/family_name") != "�һ���" &&
            me->query("family/family_name") != "����Ļ��" &&
            me->query("family/family_name") != "ؤ��" &&
            me->query("family/family_name") != "��Ĺ" ){
                me->add("shen",exp*10);
                message_vision(HIW"$N���������������ˣ�\n"NOR,me);
        }
        me->delete_temp("xy/job");
        log_file("job/xyjob", sprintf("%s %s(%s)%d���سǵõ�����%d(��������%d)��Ǳ��%d��\n",
                ctime(time())[4..19],me->name(1),me->query("id"),(int)me->query("xy/job"),exp,nexp,pot));
        return 1;
}

void no_job()
{
        delete_temp("xy/nojob");
        set("thjob",3);
        set("gbjob",3);
        set("gmjob",3);
        set("job",7);
        set("emjob",3);
}

int hit = 0;

int hit_ob(object me, object ob, int damage)
{
        hit+=2;
        if (damage > 800) return (800-damage);
        return 0;
}

int ob_hit(object me, object ob, int damage)
{
        if (!hit) return -damage*8/10;
        hit--;
        return 0;
}

