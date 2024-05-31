BEGIN;

CREATE TABLE IF NOT EXISTS public.cities
(
    id serial NOT NULL,
    city_name character varying(127) COLLATE pg_catalog."default" NOT NULL,
    fk_country integer NOT NULL,
    CONSTRAINT cities_pkey PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS public.countries
(
    id serial NOT NULL,
    country_name character varying(64) COLLATE pg_catalog."default" NOT NULL,
    CONSTRAINT countries_pkey PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS public.departments
(
    id serial NOT NULL,
    name character varying(63) COLLATE pg_catalog."default" NOT NULL,
    description text COLLATE pg_catalog."default",
    CONSTRAINT departments_pkey PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS public.jobs
(
    id serial NOT NULL,
    title character varying(64) COLLATE pg_catalog."default" NOT NULL,
    salary numeric(11, 2) NOT NULL,
    CONSTRAINT jobs_pkey PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS public.project_status
(
    id serial NOT NULL,
    status_name character varying(12) COLLATE pg_catalog."default" NOT NULL,
    CONSTRAINT project_status_pkey PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS public.projects
(
    id serial NOT NULL,
    name character varying(127) COLLATE pg_catalog."default" NOT NULL,
    description text COLLATE pg_catalog."default",
    start_date date NOT NULL,
    end_date date,
    fk_status integer NOT NULL,
    CONSTRAINT projects_pkey PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS public.worker_project
(
    fk_worker integer NOT NULL,
    fk_project integer NOT NULL,
    CONSTRAINT worker_project_pkey PRIMARY KEY (fk_worker, fk_project)
);

CREATE TABLE IF NOT EXISTS public.department_boss
(
    fk_department integer NOT NULL,
    fk_boss integer NOT NULL,
    CONSTRAINT department_boss_pkey PRIMARY KEY (fk_department)
);

CREATE TABLE IF NOT EXISTS public.workers
(
    id serial NOT NULL,
    first_name character varying(127) COLLATE pg_catalog."default" NOT NULL,
    last_name character varying(127) COLLATE pg_catalog."default" NOT NULL,
    middle_name character varying(127) COLLATE pg_catalog."default",
    birth_date date NOT NULL,
    fk_birth_city integer NOT NULL,
    fk_residence_city integer NOT NULL,
    residence_address text COLLATE pg_catalog."default",
    phone character(11) COLLATE pg_catalog."default",
    sex character(1) COLLATE pg_catalog."default" NOT NULL,
    department_id integer NOT NULL,
    fk_job integer NOT NULL,
    hire_date date NOT NULL,
    fk_mentor integer,
    CONSTRAINT workers_pkey PRIMARY KEY (id)
);

ALTER TABLE IF EXISTS public.projects
    ADD CONSTRAINT projects_fk_status_fkey FOREIGN KEY (fk_status)
    REFERENCES public.project_status (id) MATCH SIMPLE
    ON UPDATE NO ACTION
    ON DELETE NO ACTION;

ALTER TABLE IF EXISTS public.worker_project
    ADD CONSTRAINT worker_project_fk_project_fkey FOREIGN KEY (fk_project)
    REFERENCES public.projects (id) MATCH SIMPLE
    ON UPDATE NO ACTION
    ON DELETE NO ACTION;

ALTER TABLE IF EXISTS public.worker_project
    ADD CONSTRAINT worker_project_fk_worker_fkey FOREIGN KEY (fk_worker)
    REFERENCES public.workers (id) MATCH SIMPLE
    ON UPDATE NO ACTION
    ON DELETE NO ACTION;

ALTER TABLE IF EXISTS public.department_boss
    ADD CONSTRAINT department_boss_fk_worker FOREIGN KEY (fk_boss)
    REFERENCES public.workers (id) MATCH SIMPLE
    ON UPDATE NO ACTION
    ON DELETE NO ACTION;

ALTER TABLE IF EXISTS public.department_boss
    ADD CONSTRAINT department_boss_fk_department_fkey FOREIGN KEY (fk_department)
    REFERENCES public.departments (id) MATCH SIMPLE
    ON UPDATE NO ACTION
    ON DELETE NO ACTION;

ALTER TABLE IF EXISTS public.workers
    ADD CONSTRAINT workers_department_id_fkey FOREIGN KEY (department_id)
    REFERENCES public.departments (id) MATCH SIMPLE
    ON UPDATE NO ACTION
    ON DELETE NO ACTION;

ALTER TABLE IF EXISTS public.workers
    ADD CONSTRAINT workers_fk_birth_city_fkey FOREIGN KEY (fk_birth_city)
    REFERENCES public.cities (id) MATCH SIMPLE
    ON UPDATE NO ACTION
    ON DELETE NO ACTION;

ALTER TABLE IF EXISTS public.workers
    ADD CONSTRAINT workers_fk_job_fkey FOREIGN KEY (fk_job)
    REFERENCES public.jobs (id) MATCH SIMPLE
    ON UPDATE NO ACTION
    ON DELETE NO ACTION;

ALTER TABLE IF EXISTS public.workers
    ADD CONSTRAINT workers_fk_residence_city_fkey FOREIGN KEY (fk_residence_city)
    REFERENCES public.cities (id) MATCH SIMPLE
    ON UPDATE NO ACTION
    ON DELETE NO ACTION;

ALTER TABLE IF EXISTS public.workers
    ADD FOREIGN KEY (fk_mentor)
    REFERENCES public.workers (id) MATCH SIMPLE
    ON UPDATE NO ACTION
    ON DELETE NO ACTION
    NOT VALID;

ALTER TABLE IF EXISTS public.cities
    ADD CONSTRAINT cities_fk_country_fkey FOREIGN KEY (fk_country)
    REFERENCES public.countries (id) MATCH SIMPLE
    ON UPDATE NO ACTION
    ON DELETE NO ACTION;

END;
