int ask_job_s()
{
        object ob = this_player();
// �ж� ����        
        if (ob->query("family/family_name") != "�һ���")
        {
                tell_room(environment(ob),"�����ɻ�Ŀ���" + ob->query("name") + ",˵��: ʲôʦĸ��ʦĸ�ģ���ĸ���������е���?\n",({ob}));
                tell_object(ob,"�����ɻ�Ŀ�����,˵��: ʲôʦĸ��ʦĸ�ģ���ĸ���������е���?\n");
                return 1;
        }
               
        ob->set_temp("thd/job_s",1);
        say( "����̾�˿�����˵��: ��ĸ�׾�����������ϧ��Ӣ�����ţ��ҵ������������һ����ϵ�һ��Ĺ�\n");
        this_object()->start_busy(3);
        return 1;
}

int ask_job()
{
        object me = this_object();
        object ob = this_player();
        mixed *local;
        
        local = localtime(time()*60);
/*
// �ж� ʱ��        
        if (local[2] > 9 && local[2] < 17)
        {
                tell_room(environment(ob),"�����ɻ�Ŀ���" + ob->query("name") + ",˵��: ���ڴ����ģ�����ʲôĹѽ?\n",({ob}));
                tell_object(ob,"�����ɻ�Ŀ�����,˵��: ���ڴ����ģ���ʲôĹѽ?\n");
                ob->delete_temp("thd/job_s");
                return 1;
        }
*/
        if( ob->query("job_name") == "�һ���Ĺ"){
         	command("say ��ո�������Ĺ���񣬻�������Ϣһ��ɡ�");
         	return 1;
        }
         
        if (ob->query("combat_exp") > 2000000)
        {
                command("say ���书��ô�ã������鷳����");
                ob->delete_temp("thd/job_s");
                return 1;
        }

// �ж� ����        
        if ((int)ob->query("combat_exp") < 100000)
        {
                tell_room(environment(ob),"���ؿ��˿�" + ob->query("name") + ",˵��: ���书������û��ã���ôΣ�յ������Ǳ����ˣ�\n",({ob}));
                tell_object(ob,"���ؿ��˿���,˵�������书������û��ã���ôΣ�յ������Ǳ����ˣ�\n");
                ob->delete_temp("thd/job_s");
                return 1;
        }
// �ж� �Ƿ��Ѿ���������
        if ((int)ob->query_temp("thd/job")>0)
        {
                tell_room(environment(ob),"���ص���" + ob->query("name") + "һ��,˵��: ���ǽ���ȥ�����㻹���������ʲô?\n",({ob}));
                tell_object(ob,"���ص�����һ��,˵��: ���ǽ���ȥ�����㻹���������ʲô?\n");
                ob->delete_temp("thd/job_s");
                return 1;
        }
// �ж� �Ƿ�������������        
        if ((int)me->query("thd/havejob")  < 1 )
        {
                command( "say �Ѿ�����ȥ��Ĺ�ˣ����´���ȥ�ɣ�");
                ob->delete_temp("thd/job_s");
                return 1;
        }
        if ((int)ob->query_condition("thd_job") > 0)
        {
                command( "say �������Ĺ����Ϣһ����ȥ�ɣ�");
                ob->delete_temp("thd/job_s");
                return 1;
        }
// �ж� qimen-bagua�Ƿ�>=100
        if (!ob->query_temp("thd/job_s") 
        ||  ob->query_skill("qimen-bagua",1) < 80)
        {
                command( "say �ѵ�����������⣬������ĸ�׵�Ĺ���������ܽ�ȥ�ġ�");
                return 1;
        }
// job busy
 if ( ob->query_condition("job_busy") || ob->query_condition("thd_job")>0) {
    command("say �Բ�����������û��ʲô���Ը������ġ�");
return 1; }
// ��������
        switch( random(2))
        {
                case 0:
                        command( "say �ѵ�����������⣬������ĸ�׵�Ĺ���������ܽ�ȥ�ġ�");
                        break;  
                case 1:
                        command( "say ��ҪС�ĵ㣬��ĸ�׵�Ĺ�ɲ���һ���˶��ܽ�ȥ�ġ�");
                        break;
        }
        say( "���������룬˵��: ������,�Ҵ���ȥ!\n");
        ob->delete_temp("thd/job_s");
        ob->set_temp("thd/job",1);
        me->delete("thd/havejob");
   // ���� busy
        ob->apply_condition("thd_job", 3+random(3));
        ob->apply_condition("job_busy", 9);
        ob->set("job_name", "�һ���Ĺ");
        tell_object(ob,"������Ż��أ���һת����һת����һ��͵���Ĺǰ��\n");
        ob->move(__THD__"tomb");
        tell_object(ob,GRN"���������������˵��: ��Ҫ�ú���Ĺ�������ʲô�˽���Ĺ��㲻Ҫ��������!\n"NOR);
   // ���� ����ʧ��ʱ��
        call_out("job_failed",250);
        return 1;
}

int accept_object(object who, object ob)
{
        object me = this_object();
        int exp,pot,job_busy;
        
        if (!who->query_temp("thd/dojob"))
                return 0;
                        
        if (ob->query("id")=="lv feicui"
        ||  ob->query("id")=="meiyu"
        ||  ob->query("id")=="yeming zhu"
        ||  ob->query("id")=="zi manao")
        {
            if(ob->query_temp("thdjob") != who->query("id")){
                    command("hehe "+ who->query("id"));
                    command("say �������Ū����"+ob->query("name")+"���ǿɲ�����ɵ�Ŷ��");
                    return 0;
                }
                switch( random(5) )
                {
                        case 0:
                                command("pat " + who->query("id"));
                                say("������ϲ��˵������ɵĺܳ�ɫ�����Ǹ���Ľ�����\n");
                                break;
                        case 1:
                                command("nod " + who->query("id"));
                                say("����˵�������պ�Ҫ������������Ϊ�����һ�����Щ���ף�\n");
                                break;
                        case 2:
                                command("thumb " + who->query("id"));
                                say("���ؿ��˿�" + ob->query("name") + "��˵������׷���˱��������ߵı�����Ϳɲ�Сѽ��\n");
                                break;
                        case 3:
                                command("touch " + who->query("id"));
                                say("�������ֵ���" + ob->query("name") + "��˵�����ҵ����������Ū������Щ����ɶ����޼�֮��ѽ��\n");
                                break;
                        case 4:
                                command("pat " + who->query("id"));
                                say("����˵������Ϊ�����һ������˴��ף��Ҳ��������ġ�\n");
                                break;
                }
                                
// give rewards
// calculate combat_exp
                job_busy = 7 - (int)who->query_condition("thd_job");
                exp = 30 
                        + random((int)who->query("thd_job",1)/20)
                        + random(who->query("thd_job",1)/10)
                        + random((int)who->query("age",1))
                        + random((int)who->query("int",1))
                        - job_busy;
                if (exp < 150) exp = 130 + random(30);
        if(exp>250) exp=200+random(50);
                who->add("combat_exp",exp);
// calculate potential
                pot = exp/5+ random(exp/6);
/*                pot = random((int)who->query("int",1)*3)
                    + random((int)who->query("thd_job",1)/20)
                    + random(who->query_skill("qimen-bagua",1)/5)
                    + random(50)
                    + 50;
                  30
                        + random((int)who->query("thd_job",1)/40)
                        + random((int)who->query("age",1))
                        - job_busy*job_busy;
                if (pot < 50) pot = 30 + random(20);
                if (pot > 150) pot = 150 + random(10);*/
/*             if (pot < 50) pot = 30 + random(20);
                if (pot > 100) pot = 50 + random(100);
*/                who->add("potential",pot);
                   if (who->query("potential")>who->query("max_pot"))
                   who->set("potential", who->query("max_pot"));
                   who->add("balance", pot*1000);
// add log to /log/thdjobs ����ʱ�ã��ú�ȥ��
	log_file("job/thdjobs",sprintf("%s %s(%s)%d������������%d��Ǳ��%d��\n",
                ctime(time())[4..19],who->name(1),who->query("id"),(int)who->query("thd_job"),exp,pot));

// add job times
                if (!who->query("thd_job"))
                        who->set("thd_job",1);
                who->add("thd_job",1);
                who->delete_temp("thd/dojob");
// �ֿ���������������
                me->set("thd/havejob",1);
// ȥ�� job fail
                remove_call_out("job_failed");
// ����job busy time
who->apply_condition("job_busy",5+random(2));
 who->apply_condition("thd_job",4+random(3)+exp/50);
                call_out("destroy", 1, ob);
                tell_room(environment(),HIY "������"+ who->query("name")+ "�Ķ��ߵ���˵�˼��䣬"+ who->query("name") +"���Ĳ�ס��ͷ�����ϲɫ��\n"NOR, ({ who }));
                switch( random(3))
                {
                        case 0:
                                tell_object(who,HIG"��������л�Ȼ���ʣ��õ���"+CHINESE_D->chinese_number(exp)+"�㾭�飬"
                                        +CHINESE_D->chinese_number(pot)+"��Ǳ�ܡ�\n"NOR);
                                break;
                        case 1:
                                tell_object(who,HIY"������"+CHINESE_D->chinese_number(exp)+"�㾭�飬"
                                        +CHINESE_D->chinese_number(pot)+"��Ǳ�ܵĽ�����\n"NOR);
                                break;
                        case 2:
                                tell_object(who,HIR"��о�һ���������������ߣ�������"+CHINESE_D->chinese_number(exp)+"�㾭�飬"
                                        +CHINESE_D->chinese_number(pot)+"��Ǳ�ܡ�\n"NOR);
                                break;
                }
                return 1;
        }
        else return 0;
}

void job_failed()
{
        object me = this_object();
        switch( random(3))
        {
                case 0:
                        say( "����˵������ѽ��ȥ��Ĺ����С����ô����������\n");
                        break;
                case 1:
                        say( "���ؽ��ŵ�˵����ȥ��Ĺ����С�Ӳ������˰ɣ���ô��������Ӱ��\n");
                        break;
                case 2:
                        say( "����̾�˿�����˵����������Щ�书�ߵĵ���ȥ��Ĺ�ɣ�\n");
                        break;
        }
        say( "����˵�������ˣ��һ��������ұ���ȥ��Ĺ�ɣ�\n");
        me->set("thd/havejob",1);
}

void destroy(object ob)
{
        destruct(ob);
}
